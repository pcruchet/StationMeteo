function creerGraphique() {

    var options = {
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

        tooltip: {
            borderColor: '#4b85b7',
            backgroundColor: '#edf1c8'
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
                    return this.value + ' mm/h';
                },

                style: {
                    color: '#000'
                }
            },
            opposite: false
        },
        series: []
    };


    $.getJSON('../../Controleurs/controleur.php', {
        option: document.querySelector('input[name=optradio]:checked').value,
        action: 'obtenirPluviosite'})
            .done(function (laPluie) {

                var lesMesures = [];
                var lesDates = [];
                $.each(laPluie['valeurs'], function (indice, valeur) {
                    lesMesures.push(valeur);
                    lesDates.push(indice);
                });

                options.series.push({
                    name: laPluie['periode'],
                    tooltip: {
                        valueDecimals: 1,
                        valueSuffix: 'mm/h'
                    },
                    data: lesMesures
                });
                options.xAxis.categories = lesDates;

                chart = new Highcharts.chart(options);
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




