<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <!-- JQuery Bootstrap 4 -->
        <script src="../../Librairies/Javascript/jquery-3.5.0.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/bootstrap.min.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/popper-1.16.0.min.js" type="text/javascript"></script>
        <link href="../../Librairies/Css/bootstrap.min.css" rel="stylesheet" type="text/css"/>

        <!-- Hightcharts -->
        <script src="../../Librairies/Javascript/highstock.js" type="text/javascript"></script>
        <script src="../../Librairies/Javascript/exporting.js" type="text/javascript"></script>

        <script src="../Javascript/temperatureHumidite.js" type="text/javascript"></script>

        <title>Température & Humidité</title>
    </head>
    <body>
        <?php require_once 'menu.php'; ?>

        <div class="modal" id="idChoixCourbe">
            <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">

                    <div class="modal-header">
                        <h4 class="modal-title">Choix des courbes</h4>
                        <button type="button" class="close" data-dismiss="modal">&times;</button>
                    </div>

                    <div class="modal-body">
                        <div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="checkbox" value="T_EXT" id="idText">
                                <label class="form-check-label" for="idText">Température Extérieure</label>
                            </div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="checkbox" value="H_EXT" id="idHext">
                                <label class="form-check-label" for="idHext">Humidité Extérieure</label>
                            </div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="checkbox" value="T_SERRE" id="idTserre">
                                <label class="form-check-label" for="idTserre">Température de la serre</label>
                            </div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="checkbox" value="H_SERRE" id="idHserre">
                                <label class="form-check-label" for="idHserre">Humidité de la serre</label>
                            </div>
                        </div>
                    </div>

                    <div class="modal-footer">
                        <div id="idCocherTout"  class="form-check " >
                            <input class="form-check-input" type="checkbox" value="ToutCocher" id="idCocher">
                            <label class="form-check-label" for="idCocher">Cocher Tout&nbsp;&nbsp;&nbsp;</label>
                        </div>
                        <button type="button" class="btn btn-primary btn-afficher" data-dismiss="modal" id="idAfficherCourbe">Afficher</button>
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Annuler</button>
                    </div>

                </div>
            </div>
        </div>

        <div id="idTemperatureHumidite" style="padding: 50px;"></div>







    </body>
</html>

