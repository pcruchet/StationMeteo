

function creerGraphique(_dateDebut, _dateFin) {

    var couleurs = ["#ccfffe", "#b0f2b6", "98fb98", "#99ff99", "#9afe66", "#99fe00",
        "#99cc01", "#cdcc00", "#ffcc00", "#fe9900", "#ff6600", "#ff3300", "#fe0000"];
    // Parse the data from an inline table using the Highcharts Data plugin

    var chartOptions = {

        chart: {
            renderTo: 'idDistributionVent',
            height: 700,
            marginTop: 70,
            marginLeft: 100,
            marginRight: 100,
            polar: true,
            type: 'column'
        },
        title: {
            text: 'Rose des vents',
        },
        credits: {
            text: 'Météo@PCT',
            enabled: true
        },
        pane: {
            size: '90%'
        },
        legend: {
            reversed: true,
            align: 'right',
            verticalAlign: 'top',
            y: 100,
            layout: 'vertical'
        },
        xAxis: {
            tickmarkPlacement: 'on',
            categories: ["<b>Nord</b>", "NNE", "NE", "ENE", "<b>Est</b>", "ESE", "SE", "SSE", "<b>Sud</b>", "SSO", "SO", "OSO", "<b>Ouest</b>", "ONO", "NO", "NNO"]
        },
        yAxis: {
            min: 0,
            endOnTick: false,
            showLastLabel: true,
            title: {
                text: 'Frequence (%)'
            },
            labels: {
                formatter: function () {
                    return this.value + '%';
                }
            }
        },
        tooltip: {
            valueSuffix: ' %',
            valueDecimals: 1,
            followPointer: true
        },
        plotOptions: {
            series: {
                stacking: 'normal',
                shadow: false,
                groupPadding: 0,
                pointPlacement: 'on'
            }
        },
        colors: ["#ccfffe", "#b0f2b6", "#adff2f", "#7fff00", "#9afe66", "#99fe00",
            "#99cc01", "#cdcc00", "#ffcc00", "#fe9900", "#ff6600", "#ff3300", "#fe0000"],
        series: []
    };




    $.getJSON('../../Controleurs/controleur.php', {
        dateDebut: _dateDebut,
        dateFin: _dateFin,
        action: 'obtenirDistributionVent'})
            .done(function (tabValeurs) {

                var indice = 0;
                $.each(tabValeurs, function (i, valeurs) {
                    console.log(valeurs);
                    var distribution = [];
                    $.each(valeurs['data'], function (j, distrib) {
                        distribution.push(distrib);
                    });
                    chartOptions.series.push({
                        name: valeurs['name'],
                        data: distribution,
                    });
                });
                chart = new Highcharts.chart(chartOptions);
            })
            .fail(function (xhr, text, error) {
                console.log("param : " + JSON.stringify(xhr));
                console.log("status : " + text);
                console.log("error : " + error);
            });

}

$(document).ready(function () {

    $('.input-daterange').datepicker({
        startDate: "04/04/2020",
        format: "dd/mm/yyyy",
        language: "fr",
        endDate: "today",
        autoclose: true,
        todayHighlight: true
    });

    $('.input-daterange').datepicker('update', [new Date(), new Date()]);

    var option = {day: "2-digit", month: "2-digit", year: "numeric"};
    var dateDebut = new Intl.DateTimeFormat("fr-FR", option).format(new Date());

    var dateFin = dateDebut;
    $('#idDateDebut').val(dateDebut);
    $('#idDateFin').val(dateFin);

    $('#idDateDebut').on('change', function () {
        dateDebut = $('#idDateDebut').val();
        $('#idAfficherDistribution').removeAttr('disabled');
    });
    $('#idDateFin').on('change', function () {
        dateFin = $('#idDateFin').val();
        $('#idAfficherDistribution').removeAttr('disabled');
    });

    $('#idAfficherDistribution').click(function () {

        creerGraphique(dateDebut, dateFin);
    });


});