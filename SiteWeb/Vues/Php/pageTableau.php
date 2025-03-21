<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <!-- JQuery Bootstrap 4 -->
        <script src="../../Librairies/Javascript/jquery-3.5.0.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/bootstrap.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/popper-1.16.0.min.js" type="text/javascript"></script>
        <link href="../../Librairies/Css/bootstrap.min.css" rel="stylesheet" type="text/css"/>


        <!-- DatePicker -->
        <script src="../../Librairies/Javascript/bootstrap-datepicker.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/bootstrap-datepicker.fr.min.js" type="text/javascript"></script>
        <link href="../../Librairies/Css/bootstrap-datepicker.min.css" rel="stylesheet" type="text/css"/>
        <!-- DataTables -->
        <script src="../../Librairies/Javascript/jquery.dataTables.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/dataTables.bootstrap4.min.js" type="text/javascript"></script>
        <script src="../Javascript/tableau.js" type="text/javascript"></script>
        <link href="../Css/pageTableau.css" rel="stylesheet" type="text/css"/>


        <title>Temperature & HUmidité</title>
    </head>
    <body>

        <?php require_once 'menu.php'; ?>

        <div class="container" style="margin-top: 60px">

            


            <table id="idTableauMeteo" class="table table-striped table-bordered" style="width:100%">
                <thead class="table_entete">
                    <tr>
                        <th rowspan="2" style="vertical-align:middle">heures</th>
                        <th colspan="2">Extérieure</th>
                        <th colspan="2">Serre</th>
                        <th colspan="3">Vent</th>
                        <th>Pluie</th>
                    </tr>
                    <tr>
                        <td>Température</td>
                        <td>Humidité</td>
                        <td>Température</td>
                        <td>Humidité</td>
                        <td>Vitesse</td>
                        <td>Direction</td>
                        <td>Rafale</td>
                        <td>Cumul</td>
                    </tr>
                </thead>
                <tbody></tbody>
                <tfoot class="table_entete">
                    <tr>
                        <th rowspan="2" style="vertical-align:middle">heures</th>
                        <td>Température</td>
                        <td>Humidité</td>
                        <td>Température</td>
                        <td>Humidité</td>
                        <td>Vitesse</td>
                        <td>Direction</td>
                        <td>Rafale</td>
                        <td>Cumul</td>
                    </tr>
                    <tr>
                        <th colspan="2">Extérieure</th>
                        <th colspan="2">Serre</th>
                        <th colspan="3">Vent</th>
                        <th colspan="3">Pluie</th>
                    </tr>
                </tfoot>
            </table>
        </div>
    </body>
</html>

