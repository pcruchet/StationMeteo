<?php

require_once ("ModeleBdd.php");

/**
 * Description of TableauMeteorologique
 *
 * @author philippe
 */
class TableauMeteorologique extends ModeleBdd {

    protected $data = [];       /// Tableau contenant les données à afficher.
    protected $indice = 0;
    protected $indiceExterieure = 0;
    protected $indiceSerre = 0;

    private function AjouterTemperatureHumiditeExterieure($_heure, $_temperature, $_humidite) {

        if (!isset($this->data[$this->indiceExterieure])) {
            array_push($this->data, array(
                'id' => $this->indice++,
                $_heure,
                $_temperature,
                $_humidite,
                0,
                0,
                " ",
                " ",
                " ",
                " "
            ));
        } else {
            $this->data[$this->indiceExterieure][1] = $_temperature;
            $this->data[$this->indiceExterieure][2] = $_humidite;
        }
        $this->indiceExterieure++;
    }

    private function AjouterTemperatureHumiditeSerre($_heure, $_temperature, $_humidite) {

        if (!isset($this->data[$this->indiceSerre])) {
            array_push($this->data, array(
                'id' => $this->indice++,
                $_heure,
                0,
                0,
                $_temperature,
                $_humidite,
                " ",
                " ",
                " ",
                " "
            ));
        } else {
            $this->data[$this->indiceSerre][3] = $_temperature;
            $this->data[$this->indiceSerre][4] = $_humidite;
        }
        $this->indiceSerre++;
    }

    private function CalculerIndice($_heure) {

        $heures = intval(substr($_heure, 0, 2));
        $minutes = intval(substr($_heure, 3, 2));

        return ($heures * 2 + ($minutes == 30 ? 1 : 0));
    }

    private function ObtenirVent($_dateDebut, $_dateFin) {
        $requete = $this->_bdd->prepare("SELECT * FROM `Vent` WHERE  horodatage >= :dateDebut AND horodatage < :dateFin;");
        $requete->bindParam(":dateDebut", $_dateDebut);
        $requete->bindParam(":dateFin", $_dateFin);

        $requete->execute() or die(print_r($requete->errorInfo()));
        while ($ligne = $requete->fetch()) {

            $date = new DateTime($ligne['horodatage']);
            $heureCourante = $date->format('H:i');
            $vitesse = floatval($ligne['vitesse']);
            $direction = intval($ligne['direction']);
            $rafale = floatval($ligne['rafale']);

            $indice = $this->CalculerIndice($heureCourante);
            $this->data[$indice][5] = $vitesse;
            $this->data[$indice][6] = $direction;
            $this->data[$indice][7] = $rafale;
        }
        $requete->closeCursor();
    }

    private function ObtenirPluie($_dateDebut, $_dateFin) {

        $requete = $this->_bdd->prepare("SELECT * FROM `Pluie` WHERE  horodatage >= :dateDebut AND horodatage < :dateFin;");
        $requete->bindParam(":dateDebut", $_dateDebut);
        $requete->bindParam(":dateFin", $_dateFin);

        $requete->execute() or die(print_r($requete->errorInfo()));
        while ($ligne = $requete->fetch()) {

            $date = new DateTime($ligne['horodatage']);
            $heureCourante = $date->format('H:i');
            $quantite = floatval($ligne['quantite']);

            $indice = $this->CalculerIndice($heureCourante);
            $this->data[$indice][8] = $quantite;
        }
        $requete->closeCursor();
    }

    public function ObtenirDonnesMeteorologique($jourSelection) {


        try {

            $this->Connexion();
            $requete = $this->_bdd->prepare("SELECT * FROM `TemperatureHumidite` WHERE  horodatage >= :dateDebut AND horodatage < :dateFin;");

            $dateDebut = new DateTime($jourSelection);
            $dateFin = new DateTime($jourSelection);
            $dateFin->add(new DateInterval('P0Y0M1DT0H0M0S'));

            $varDebut = $dateDebut->format("Y-m-d H:i:s");
            $requete->bindParam(":dateDebut", $varDebut);
            $varFin = $dateFin->format("Y-m-d H:i:s");
            $requete->bindParam(":dateFin", $varFin);

            $requete->execute() or die(print_r($requete->errorInfo()));

            if ($ligne = $requete->fetch()) {

                $laDate = date('Y-m-d H:i', strtotime($ligne['horodatage']));   // afin d'ignorer les secondes
                $date = new DateTime($laDate);
                $datePrecExterieur = $date;
                $datePrecSerre = $date;


                $heureCourante = $date->format('H:i');
                $temperature = floatval($ligne['temperature']);
                $humidite = intval($ligne['humidite']);
                $idStation = intval($ligne['idStation']);

                if ($idStation === 71) {
                    $this->AjouterTemperatureHumiditeExterieure($heureCourante, $temperature, $humidite);
                }
                if ($idStation === 169) {
                    $this->AjouterTemperatureHumiditeSerre($heureCourante, $temperature, $humidite);
                }

                while ($ligne = $requete->fetch()) {

                    $laDate = date('Y-m-d H:i', strtotime($ligne['horodatage']));
                    $date = new DateTime($laDate);

                    $heureCourante = $date->format('H:i');
                    $temperature = floatval($ligne['temperature']);
                    $humidite = intval($ligne['humidite']);
                    $idStation = intval($ligne['idStation']);

                    if ($idStation === 71) {
                        $diff = ($date->getTimestamp() - $datePrecExterieur->getTimestamp());
                        
                        while ($diff > 1800) { // 30 minutes
                            $datePrecExterieur->add(new DateInterval('P0Y0M0DT0H30M0S')); 
                            $heureCouranteE = $datePrecExterieur->format('H:i');
                            $temperatureE = $this->data[$this->indiceExterieure - 1][1];
                            $humiditeE = $this->data[$this->indiceExterieure - 1][2];
                            $this->AjouterTemperatureHumiditeExterieure($heureCouranteE, $temperatureE, $humiditeE);
                            $diff = ($date->getTimestamp() - $datePrecExterieur->getTimestamp());
                        }
                        
                        $this->AjouterTemperatureHumiditeExterieure($heureCourante, $temperature, $humidite);
                        $datePrecExterieur = $date;
                    }

                    if ($idStation === 169) {
                        $diff = ($date->getTimestamp() - $datePrecSerre->getTimestamp());
                        while ($diff > 1800) { // 30 minutes
                            $datePrecSerre->add(new DateInterval('P0Y0M0DT0H30M0S'));
                            $heureCouranteS = $datePrecSerre->format('H:i');
                            $temperatureS = $this->data[$this->indiceSerre - 1][1];
                            $humiditeS = $this->data[$this->indiceSerre - 1][2];
                            $this->AjouterTemperatureHumiditeSerre($heureCouranteS, $temperatureS, $humiditeS);
                            $diff = ($date->getTimestamp() - $datePrecSerre->getTimestamp());
                        }
                        
                        $this->AjouterTemperatureHumiditeSerre($heureCourante, $temperature, $humidite);
                        $datePrecSerre = $date;
                    }
                }
                $requete->closeCursor();
                $this->ObtenirVent($varDebut, $varFin);
                $this->ObtenirPluie($varDebut, $varFin);

                header('Content-Type: application/json; charset=utf-8');
                echo json_encode($this->data, JSON_NUMERIC_CHECK);
            }
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "</br>";
            die();
        }
    }

}
