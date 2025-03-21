<?php

require_once ("ModeleBdd.php");

/**
 * Description of TemperatureHumidite
 *
 * @author philippe
 */
class TemperatureHumidite extends ModeleBdd {

    protected $courbes = [];

    public function ObtenirTemperatureHumidite($_tempExt, $_humExt, $_tempSerre, $_humSerre) {

        $this->Connexion();

        $temperaturesExterieure = [];
        $hygrometrieExterieur = [];
        $temperaturesSerre = [];
        $hygrometrieSerre = [];

        $requete = $this->_bdd->query("SELECT * FROM `TemperatureHumidite` WHERE horodatage >= '2020-04-04 00:00';");

        $iExterieur = 0;
        $iSerre = 0;
        if ($ligne = $requete->fetch()) {


            $laDate = date('Y-m-d H:i', strtotime($ligne['horodatage']));
            $dateDepart = new DateTime($laDate);

            $date = $dateDepart;
            $datePrecExterieur = $dateDepart;
            $datePrecSerre = $dateDepart;

            $temperature = floatval($ligne['temperature']);
            $humidite = intval($ligne['humidite']);
            $idStation = intval($ligne['idStation']);

            if ($idStation === 71) {
                $temperaturesExterieure[$iExterieur] = $temperature;
                $hygrometrieExterieur[$iExterieur++] = $humidite;
            }

            if ($idStation === 169) {
                $temperaturesSerre[$iSerre] = $temperature;
                $hygrometrieSerre[$iSerre++] = $humidite;
            }

            while ($ligne = $requete->fetch()) {

                $laDate = date('Y-m-d H:i', strtotime($ligne['horodatage']));
                $date = new DateTime($laDate);
                $temperature = floatval($ligne['temperature']);
                $humidite = intval($ligne['humidite']);
                $idStation = intval($ligne['idStation']);

                if ($idStation === 71) {
                    $diff = ($date->getTimestamp() - $datePrecExterieur->getTimestamp());
                    while ($diff > 1800) {
                        $datePrecExterieur->add(new DateInterval('P0Y0M0DT0H30M0S'));
                        $temperaturesExterieure[$iExterieur] = $temperaturesExterieure[$iExterieur - 1];
                        $hygrometrieExterieur[$iExterieur] = $hygrometrieExterieur[$iExterieur - 1];
                        $diff = ($date->getTimestamp() - $datePrecExterieur->getTimestamp());
                        $iExterieur++;
                    }
                    $temperaturesExterieure[$iExterieur] = $temperature;
                    $hygrometrieExterieur[$iExterieur++] = $humidite;
                    $datePrecExterieur = $date;
                }

                if ($idStation === 169) {
                    $diff = ($date->getTimestamp() - $datePrecSerre->getTimestamp());
                    while ($diff > 1800) {
                        $datePrecSerre->add(new DateInterval('P0Y0M0DT0H30M0S'));
                        $temperaturesSerre[$iSerre] = $temperaturesSerre[$iSerre - 1];
                        $hygrometrieSerre[$iSerre] = $hygrometrieSerre[$iSerre - 1];
                        $diff = ($date->getTimestamp() - $datePrecSerre->getTimestamp());
                        $iSerre++;
                    }
                    $temperaturesSerre[$iSerre] = $temperature;
                    $hygrometrieSerre[$iSerre++] = $humidite;
                    $datePrecSerre = $date;
                }
            }

            $requete->closeCursor();

            $this->courbes['origine'] = $dateDepart;
            if ($_tempExt) {
                $this->courbes[] = array(
                    'nom' => 'Temperature extérieure',
                    'mesures' => $temperaturesExterieure,
                    'axe' => 0,
                    'unite' => ' °C'
                );
            }
            if ($_humExt) {
                $this->courbes[] = array(
                    'nom' => 'Humidité extérieure',
                    'mesures' => $hygrometrieExterieur,
                    'axe' => 1,
                    'unite' => ' %'
                );
            }
            if ($_tempSerre) {
                $this->courbes[] = array(
                    'nom' => 'Temperature serre',
                    'mesures' => $temperaturesSerre,
                    'axe' => 0,
                    'unite' => ' °C'
                );
            }
            if ($_humSerre) {
                $this->courbes[] = array(
                    'nom' => 'Humidité serre',
                    'mesures' => $hygrometrieSerre,
                    'axe' => 1,
                    'unite' => ' %'
                );
            }

            header("Access-Control-Allow-Origin: *");
            header('Content-type: application/json');
            echo json_encode($this->courbes, JSON_FORCE_OBJECT);
        }
    }

}
