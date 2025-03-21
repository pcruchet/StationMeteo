<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <script src="../../Librairies/Javascript/jquery-3.5.0.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/bootstrap.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/popper-1.16.0.min.js" type="text/javascript"></script>
        <link href="../../Librairies/Css/bootstrap.min.css" rel="stylesheet" type="text/css"/>

        <script src="../../Librairies/Javascript/highcharts.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/highcharts-more.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/hightcharts-module-data.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/exporting.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/hightcharts-module-export-data.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/hightcharts-modules-accessibility.js" type="text/javascript"></script>

        <!-- DatePicker -->
        <script src="../../Librairies/Javascript/bootstrap-datepicker.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/bootstrap-datepicker.fr.min.js" type="text/javascript"></script>
        <link href="../../Librairies/Css/bootstrap-datepicker.min.css" rel="stylesheet" type="text/css"/>


        <link href="../Css/pageVent.css" rel="stylesheet" type="text/css"/>
        <script src="../Javascript/vent.js" type="text/javascript"></script>
        <title>Vent</title>
    </head>
    <body>
        <?php require_once 'menu.php'; ?>
        <div class="container" style="margin-top: 60px ">
            <div class="row col-sm-12">
                <h1>Distribution de la vitesse et de la direction du vent</h1>
                <div class="row col-md-6 col-sm-12">
                    <div class="input-group  input-daterange " id="idPeriode" >
                        <label class="form-check-label" for="idPeriode" style="margin-top: auto; margin-bottom: auto"><b>Période du :&nbsp;</b></label>
                        <input type="text" class="form-control" style="cursor: pointer;" id="idDateDebut">
                        <div class="input-group-addon" style="margin-top: auto; margin-bottom: auto"><b>&nbsp; au &nbsp;</b></div>
                        <input type="text" class="form-control" style="cursor: pointer;" id="idDateFin">&nbsp;&nbsp;&nbsp;
                        <button type="button" class="btn btn-primary btn-afficher" id="idAfficherDistribution" disabled="">Afficher</button>
                    </div>
                </div>
            </div>
            <div class="row col-md-6 col-sm-12"></div>
        </div>
        <div class="row" >
            <div id="idDistributionVent" style="width: 100%"></div>
        </div>
    </div>
</body>        
</html>
