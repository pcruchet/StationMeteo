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
        <script src="../Javascript/pluie.js" type="text/javascript"></script>
        
        <title></title>
    </head>
    <body>
        
        <?php require_once 'menu.php'; ?>
        <div class="modal" id="idChoixFrequence">
            <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">

                    <div class="modal-header">
                        <h4 class="modal-title">Choix de la fréquence</h4>
                        <button type="button" class="close" data-dismiss="modal">&times;</button>
                    </div>

                    <div class="modal-body">
                        <div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="radio" value="heure" name="optradio" id="idheure" checked>
                                <label class="form-check-label" for="idheure">Par heure</label>
                            </div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="radio" value="jour" name="optradio" id="idjour">
                                <label class="form-check-label" for="idjour">Par jour</label>
                            </div>
                            <div id="idChoix" class="form-check">
                                <input class="form-check-input" type="radio" value="mois" name="optradio" id="idmois">
                                <label class="form-check-label" for="idmois">Par mois</label>
                            </div>
                        </div>
                    </div>

                    <div class="modal-footer">
                        <button type="button" class="btn btn-primary btn-afficher" data-dismiss="modal" id="idAfficherPluviosite">Afficher</button>
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Annuler</button>
                    </div>

                </div>
            </div>
        </div>
        
        <div>
            <div id="idCumulPluie" style="padding: 50px;"></div>
        </div>
    </body>
</html>
