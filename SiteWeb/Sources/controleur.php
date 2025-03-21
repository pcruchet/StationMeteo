<?php

require_once '../Modeles/TableauMeteorologique.php';
require_once '../Modeles/TemperatureHumidite.php';
require_once '../Modeles/Pluie.php';
require_once '../Modeles/Vent.php';

if (filter_input(INPUT_SERVER, 'REQUEST_METHOD') == 'GET') {
    $action = filter_input(INPUT_GET, "action");
    switch ($action) {
        case 'obtenirDonneesMeteorologiques':
            $date = filter_input(INPUT_GET, 'dateDuJour', FILTER_DEFAULT);
            if (isset($date)) {
                $tableau = new TableauMeteorologique;
                $tableau->ObtenirDonnesMeteorologique($date);
            }
            break;
        case 'obtenirTemperatureHumidite' :
            $tempExt = filter_input(INPUT_GET, 'tempExt', FILTER_VALIDATE_BOOLEAN);
            $humExt = filter_input(INPUT_GET, 'humExt', FILTER_VALIDATE_BOOLEAN);
            $tempSerre = filter_input(INPUT_GET, 'tempSerre', FILTER_VALIDATE_BOOLEAN);
            $humSerre = filter_input(INPUT_GET, 'humSerre', FILTER_VALIDATE_BOOLEAN);
            if (isset($tempExt) || isset($humExt) || isset($tempSerre) || isset($humSerre)) {
                $graphique = new TemperatureHumidite;
                $graphique->ObtenirTemperatureHumidite($tempExt, $humExt, $tempSerre, $humSerre);
            }
            break;
        case 'obtenirPluviosite':
            $frequence = filter_input(INPUT_GET, 'option', FILTER_DEFAULT);

            if (isset($frequence)) {
                $barre = new Pluie;
                switch ($frequence) {
                    case "heure":
                        $barre->ObtenirPluviositeHoraire();
                        break;
                    case "jour":
                        $barre->ObtenirPluviositeJournaliere();
                        break;
                    case "mois":
                        $barre->ObtenirPluviositeMensuelle();
                        break;
                }
            }
            break;
        case 'obtenirDistributionVent':
            $dateDebut = filter_input(INPUT_GET, 'dateDebut', FILTER_DEFAULT);
            $dateFin = filter_input(INPUT_GET, 'dateFin', FILTER_DEFAULT);
            if (isset($dateDebut) && isset($dateFin)) {
                $leVent = new Vent;
                $leVent->ObtenirDistributionVent($dateDebut, $dateFin);
            }
            break;
    }
}
