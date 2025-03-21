
$(document).ready(function () {

    $('#idTableauMeteo').DataTable({

        "retrieve": true,
        "fixedHeader": true,
        "order": [
            [0, "desc"]
        ],
        "searching": false,
        "language": {
            "lengthMenu": "Afficher _MENU_ lignes par page",
            "info": "page _PAGE_ sur _PAGES_",
            "infoEmpty": "pas de résultat",
            emptyTable: "Selectionnez une date pour visualiser des données",
            "paginate": {
                "first": "Premier",
                "last": "Dernier",
                "next": "Suivant",
                "previous": "Precedent"
            }
        },
        columnDefs: [
            {
                targets: 0,
                render: function (data, type, row) {
                    return '<b>' + data + '</b>';
                }
            },
            {
                targets: 1,
                render: function (data, type, row) {
                    return data + '<small>&nbsp;°C</small>';
                }
            },
            {
                targets: 2,
                render: function (data, type, row) {
                    return data + '<small>&nbsp;%</small>';
                }
            },
            {
                targets: 3,
                render: function (data, type, row) {
                    return data + '<small>&nbsp;°C</small>';
                }
            },
            {
                targets: 4,
                render: function (data, type, row) {
                    return data + '<small>&nbsp;%</small>';
                }
            },
            {
                targets: 5,
                render: function (data, type, row) {
                    return data !== ' ' ? data + '<small>&nbsp;km/h</small>' : '';
                }
            },
            {
                targets: 6,
                render: function (data, type, row) {
                    return data !== ' ' ? data + '<small>&nbsp;°</small>' : '';
                }
            },
            {
                targets: 7,
                render: function (data, type, row) {
                    return data !== ' ' ? data + '<small>&nbsp;km/h</small>' : '';
                }
            },
            {
                targets: 8,
                render: function (data, type, row) {
                    return data !== ' ' ? data + '<small>&nbsp;mm/h</small>' : '';
                }
            }
        ],
        "rowCallback": function (row, data) {
            var valeur = parseFloat(data[3]);
            if (valeur > 30) {
                $('td', row).addClass('alerteHaute');
            }
            if (valeur < 5) {
                $('td', row).addClass('alerteBasse');
            }

        }
    });

    $('#idTableauMeteo_wrapper').find('div').eq(3).html(
            '<div class="datepicker date input-group  shadow-sm" >' +
            '   <div style=" margin: auto">&nbsp;Date :&nbsp;&nbsp;</div>' +
            '   <input type="text" placeholder="Sélectionnez la date à visualiser" class="form-control" id="reservationDate">' +
            '   <div class="input-group-append"><span class="input-group-text "><i class="fa fa-clock-o"></i></span></div>' +
            '</div>'
            );

    $('.datepicker').datepicker({
        format: "dd-mm-yyyy",
        todayBtn: "linked",
        startDate: "04-04-2020",
        endDate: "today",
        language: "fr",
        autoclose: true,
        toggleActive: true,
        todayHighlight: true,
       
    });
      
    $('#reservationDate').on('change', function () {
        var pickedDate = $('input').val();
        $.getJSON('../../Controleurs/controleur.php', {dateDuJour: pickedDate, action: 'obtenirDonneesMeteorologiques'})
                .done(function (tabValeurs) {
                    $('#idTableauMeteo').DataTable().clear().draw();
                    $('#idTableauMeteo').DataTable().rows.add(tabValeurs).draw();
                })
                .fail(function (xhr, text, error) {
                    console.log("param : " + JSON.stringify(xhr));
                    console.log("status : " + text);
                    console.log("error : " + error);
                });
    });
});

