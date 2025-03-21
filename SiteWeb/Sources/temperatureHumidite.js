function obtenirDateDepart(date) {
    return Date.UTC(date.substring(0, 4), date.substring(5, 7) - 1, date.substring(8, 10), date.substring(11, 13), date.substring(14, 16));
}

function cocherTout(etat, formulaire)
{
    var cases = document.getElementsByClassName(formulaire);   // on recupere tous les éléments ayant la classe formulaire
    console.log(cases);
    for (var i = 0; i < cases.length -1 ; i++)     // on les parcourt
        if (cases[i].type == 'checkbox')     // si on a une checkbox...
        {
            cases[i].prop(checked,etat);
        }
}

function creerGraphique()
{
    $.getJSON('../../Controleurs/controleur.php', {
        tempExt: document.getElementById("idText").checked,
        humExt: document.getElementById("idHext").checked,
        tempSerre: document.getElementById("idTserre").checked,
        humSerre: document.getElementById("idHserre").checked,
        action: 'obtenirTemperatureHumidite'})
            .done(function (tabValeurs) {

                var chartOptions = {

                    chart: {
                        renderTo: 'idTemperatureHumidite',
                        zoomType: 'x',
                        height: 700,
                        marginTop: 70,
                        marginLeft: 100,
                        marginRight: 100,
                        backgroundColor: '#F9F9F9',
                        alignTicks: true,
                        type: 'spline',

                    },
                    rangeSelector: {

                        buttons: [{
                                type: 'day',
                                count: 1,
                                text: '24h'
                            },
                            {
                                type: 'day',
                                count: 2,
                                text: '48h'
                            }, {
                                type: 'week',
                                count: 1,
                                text: 'Sem'
                            }, {
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
                                valueDecimals: 2,
                                xDateFormat: '%A %e %b à  %Hh%M',
                                enabledIndicators: true
                            },
                    yAxis: [{
                            title: {
                                text: ''

                            },
                            TickInterval: 5,
                            labels: {

                                formatter: function () {
                                    return this.value + ' °C';
                                },

                                style: {
                                    color: '#000'
                                }
                            },
                            opposite: false
                        },
                        {
                            title: {
                                text: '',
                                x: 15
                            },

                            labels: {
                                x: 20,

                                formatter: function () {
                                    return this.value + ' %';
                                },

                                style: {
                                    color: '#000'
                                }
                            },
                            opposite: true
                        }

                    ],

                    legend: {
                        enabled: true
                    },
                    credits: {
                        text: 'Météo@PCT',
                        enabled: true
                    },
                    title: {
                        text: 'Relevés météorologiques du jardin',
                        y: 20,
                        style: {
                            color: '#212529',
                            fontSize: 20,
                            fontWeight: 'bold'
                        }
                    },
                    series: []
                };

                var axe0 = false;
                var axe1 = false;
                var nbCourbes = Object.keys(tabValeurs).length - 1;

                for (var numCourbes = 0; numCourbes < nbCourbes; numCourbes++)
                {
                    var lesMesures = [];
                    $.each(tabValeurs[numCourbes]['mesures'], function (indice, valeur) {
                        lesMesures.push(valeur);
                    });
                    chartOptions.series.push({
                        name: tabValeurs[numCourbes]['nom'],
                        pointStart: obtenirDateDepart(tabValeurs['origine']['date']),
                        pointInterval: 1800000,
                        yAxis: tabValeurs[numCourbes]['axe'],
                        tooltip: {
                            valueDecimals: 1,
                            valueSuffix: tabValeurs[numCourbes]['unite']
                        },
                        data: lesMesures

                    });
                    lesMesures = [];
                    if (tabValeurs[numCourbes]['axe'] === 0)
                    {
                        chartOptions.yAxis[0]['title'].text = "Température";
                    }
                    if (tabValeurs[numCourbes]['axe'] === 1)
                    {
                        chartOptions.yAxis[1]['title'].text = "Humidité";
                    }
                }

                dynamicChart = new Highcharts.stockChart(chartOptions);
            })
            .fail(function (xhr, text, error) {
                console.log("param : " + JSON.stringify(xhr));
                console.log("status : " + text);
                console.log("error : " + error);
            })



}

Highcharts.setOptions(
        {
            lang: {
                months: ["Janvier ", "Février ", "Mars ", "Avril ", "Mai ", "Juin ", "Juillet ", "Août ", "Septembre ", "Octobre ", "Novembre ", "Décembre "],
                weekdays: ["Dimanche ", "Lundi ", "Mardi ", "Mercredi ", "Jeudi ", "Vendredi ", "Samedi "],
                shortMonths: ['Jan', 'Fév', 'Mar', 'Avr', 'Mai', 'Juin', 'Juil', 'Août', 'Sept', 'Oct', 'Nov', 'Déc'],
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

$(document).ready(function () {

    $('#idChoixCourbe').modal('toggle');
    $('#idCocherTout').click(function () {   
        $(':checkbox.form-check-input').prop('checked',$('#idCocher').is(':checked'));
    });
    $('#idAfficherCourbe').click(function () {
        creerGraphique();
    });

});
        