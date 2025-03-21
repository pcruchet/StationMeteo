
function creerGraphique() {

    var chartOptions = {
        chart: {
            renderTo: 'idCumulPluie',
            height: 700,
            marginTop: 70,
            marginLeft: 100,
            marginRight: 100,
            backgroundColor: '#F9F9F9',
            alignTicks: true,
            type: 'column'
        },
        rangeSelector: {

            buttons: [{
                    type: 'week',
                    count: 1,
                    text: '1Sem'
                }, {
                    type: 'week',
                    count: 2,
                    text: '2Sem'
                }, {
                    type: 'week',
                    count: 3,
                    text: '3Sem'
                },
                {
                    type: 'month',
                    count: 1,
                    text: 'Mois'
                }, {
                    type: 'year',
                    count: 1,
                    text: 'Année'
                }, {
                    type: 'all',
                    text: 'Tout'
                }],
            selected: 0,
            inputDateFormat: '%e %b %Y',
            inputEditDateFormat: '%d-%m-%Y',
            buttonPosition: {
                x: -20,
                y: -20
            },
            inputPosition: {
                x: -20,
                y: -20
            }
        },

        tooltip:
                {
                    borderColor: '#4b85b7',
                    backgroundColor: '#edf1c8',
                    valueDecimals: 1,
                    xDateFormat: '%A %e %b %Y',
                    enabledIndicators: true
                },
        credits: {
            text: 'Météo@PCT',
            enabled: true
        },
        xAxis: {
            categories: [],
            crosshair: true
        },
        title: {
            text: "Pluviosité",
            margin: 10
        },
        yAxis: {
            title: {
                text: 'Cumul de pluie'
            },
            labels: {
                formatter: function () {
                    return this.value + ' mm';
                },

                style: {
                    color: '#000'
                }
            },
            opposite: false
        },
        plotOptions: {
            series: {
                pointStart: null,
                pointIntervalUnit: ''
            }
        },
        series: []
    };

    Highcharts.setOptions(
            {
                lang: {
                    months: ["Janvier ", "Février ", "Mars ", "Avril ", "Mai ", "Juin ", "Juillet ", "Août ", "Septembre ", "Octobre ", "Novembre ", "Décembre "],
                    weekdays: ["Dimanche ", "Lundi ", "Mardi ", "Mercredi ", "Jeudi ", "Vendredi ", "Samedi "],
                    shortMonths: ['Jan', 'Fév', 'Mars', 'Avr', 'Mai', 'Juin', 'Juil', 'Août', 'Sept', 'Oct', 'Nov', 'Déc'],
                    decimalPoint: ',',
                    resetZoom: 'Reset zoom',
                    resetZoomTitle: 'Reset zoom à  1:1',
                    downloadPNG: "Télécharger au format PNG image",
                    downloadJPEG: "Télécharger au format JPEG image",
                    downloadPDF: "Télécharger au format PDF document",
                    downloadSVG: "Télécharger au format SVG vector image",
                    exportButtonTitle: "Exporter image ou document",
                    printChart: "Imprimer le graphique",
                    noData: "Aucune donnée à  afficher",
                    loading: "Chargement...",
                    rangeSelectorFrom: "Entre le",
                    rangeSelectorTo: "et le",
                    viewFullscreen: "Vue pleine écran"
                }

            });


    var option = document.querySelector('input[name=optradio]:checked').value;
    $.getJSON('../../Controleurs/controleur.php', {
        option: option,
        action: 'obtenirPluviosite'})
            .done(function (laPluie) {

                var lesMesures = [];
                var lesDates = [];
                $.each(laPluie['valeurs'], function (indice, valeur) {
                    lesMesures.push(valeur);
                    lesDates.push(indice);
                });
                chartOptions.series.push({
                            name: laPluie['periode'],
                            tooltip: {
                                valueDecimals: 1,
                                valueSuffix: ' mm'
                            },
                            data: lesMesures
                        });

                
                switch (option) {
                    case 'heure':
                        chartOptions.xAxis.categories = lesDates;
                        chart = new Highcharts.chart(chartOptions);
                        break;
                    case 'jour':        
                        chartOptions.plotOptions['series']['pointStart']= Date.UTC(2020, 2, 31); // 31-03-2020
                        chartOptions.plotOptions['series']['pointIntervalUnit']= 'day';               
                        chart = new Highcharts.stockChart(chartOptions);
                        break;
                    case 'mois':
                        chartOptions.plotOptions['series']['pointStart']= Date.UTC(2020, 1, 31); // 1 mois de décallage en plus
                        chartOptions.plotOptions['series']['pointIntervalUnit']= 'month';   
                        chartOptions.tooltip['xDateFormat'] = '%B %Y';        
                        chart = new Highcharts.stockChart(chartOptions);
                        break;
                }

            })
            .fail(function (xhr, text, error) {
                console.log("param : " + JSON.stringify(xhr));
                console.log("status : " + text);
                console.log("error : " + error);
            });
}

$(document).ready(function () {

    $('#idChoixFrequence').modal('toggle');
    $('#idAfficherPluviosite').click(function () {
        creerGraphique();
    });
});




