<?php

require_once ("ModeleBdd.php");
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Pluie
 *
 * @author philippe
 */
class Pluie extends ModeleBdd {
    
    private function CalculerMoisEntre2Dates($debut, $fin) {
            $interval = $debut->diff($fin);
            $difference = $interval->m + $interval->y * 12;       
            return $difference;
        }

    public function ObtenirPluviositeHoraire() {
        try {
            $this->Connexion();
            $requete = $this->_bdd->query("SELECT * FROM `Pluie`;");
            $valeurs = array();
            while ($ligne = $requete->fetch()) {
                $date = new DateTime($ligne['horodatage']);
                $valeurs[$date->format('d-m-Y H:i')] = floatval($ligne['quantite']);
            }
            $requete->closeCursor();

            $courbe = array(
                'periode' => "Cumul de pluie par heure",
                'valeurs' => $valeurs
            );
            header("Access-Control-Allow-Origin: *");
            header('Content-type: application/json');
            echo json_encode($courbe, JSON_FORCE_OBJECT);
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "<br/>";
            die();
        }
    }

    public function ObtenirPluviositeJournaliere() {
        try {
            $this->Connexion();
            $requete = $this->_bdd->query("SELECT * FROM `Pluie`;");
            $valeurs = array();
            if ($ligne = $requete->fetch()) {
                $date = new DateTime($ligne['horodatage']);
                $datePrec = $date;
                $valeurs[$date->format('d-m-Y')] = floatval($ligne['quantite']);
                while ($ligne = $requete->fetch()) {
                    $date = new DateTime($ligne['horodatage']);
                    if (strcmp($datePrec->format('d-m-Y'), $date->format('d-m-Y')) === 0) {
                        $valeurs[$datePrec->format('d-m-Y')] += floatval($ligne['quantite']);
                    } else {
                        $diff = $date->diff($datePrec);
                        while ($diff->days > 1) {
                            date_add($datePrec, date_interval_create_from_date_string('1 days'));
                            $valeurs[$datePrec->format('d-m-Y')] = 0;
                            $diff = $date->diff($datePrec);
                        }
                        $valeurs[$date->format('d-m-Y')] = floatval($ligne['quantite']);
                        $datePrec = $date;
                    }
                }
            }
            $requete->closeCursor();

            $courbe = array(
                'periode' => "Cumul de pluie par jour",
                'valeurs' => $valeurs
            );

            header("Access-Control-Allow-Origin: *");
            header('Content-type: application/json');
            echo json_encode($courbe, JSON_FORCE_OBJECT);
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "<br/>";
            die();
        }
    }

    public function ObtenirPluviositeMensuelle() {
        try {
            $this->Connexion();
            $requete = $this->_bdd->query("SELECT * FROM `Pluie`;");
            $valeurs = array();
            if ($ligne = $requete->fetch()) {
                $date = new DateTime($ligne['horodatage']);
                $datePrec = $date;
                $valeurs[$date->format('m-Y')] = floatval($ligne['quantite']);
                while ($ligne = $requete->fetch()) {
                    $date = new DateTime($ligne['horodatage']);
                    if (strcmp($datePrec->format('m-Y'), $date->format('m-Y')) === 0) {
                        $valeurs[$datePrec->format('m-Y')] += floatval($ligne['quantite']);
                    } else {
                        $diff = $this->CalculerMoisEntre2Dates($date,$datePrec);
                        while ($diff > 1) {
                            date_add($datePrec, date_interval_create_from_date_string('1 month'));
                            $valeurs[$datePrec->format('m-Y')] = 0;
                            $diff = $date->diff($datePrec);
                        }
                        $valeurs[$date->format('m-Y')] = floatval($ligne['quantite']);
                        $datePrec = $date;
                    }
                }
            }
            $requete->closeCursor();

            $courbe = array(
                'periode' => "Cumul de pluie par jour",
                'valeurs' => $valeurs
            );

            header("Access-Control-Allow-Origin: *");
            header('Content-type: application/json');
            echo json_encode($courbe, JSON_FORCE_OBJECT);
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "<br/>";
            die();
        }
    }
    

    public function ObtenirPluviositeHoraireComplete() {
        try {
            $this->Connexion();
            $requete = $this->_bdd->query("SELECT * FROM `Pluie`;");

            if ($ligne = $requete->fetch()) {

                $valeurs = [];
                $indice = 0;

                $dateDepart = new DateTime($ligne['horodatage']);
                $date = $dateDepart;
                $datePrec = $date;

                $pluviosite = floatval($ligne['quantite']);

                $valeurs[$date->format('d-m-Y H:i')] = $pluviosite;

                while ($ligne = $requete->fetch()) {

                    $date = new DateTime($ligne['horodatage']);
                    $diff = ($date->getTimestamp() - $datePrec->getTimestamp());

                    while ($diff > 3600) {

                        $datePrec->add(new DateInterval('P0Y0M0DT1H0M0S'));
                        $pluviosite = 0;
                        $valeurs[$datePrec->format('d-m-Y H:i')] = $pluviosite;
                        $diff = ($date->getTimestamp() - $datePrec->getTimestamp());
                    }
                    $date = new DateTime($ligne['horodatage']);
                    $pluviosite = floatval($ligne['quantite']);
                    $valeurs[$date->format('d-m-Y H:i')] = $pluviosite;
                    $datePrec = $date;
                }

                $requete->closeCursor();
                $courbe = [];
                $courbe = array(
                    'origine' => $dateDepart,
                    'periode' => "heure",
                    'valeurs' => $valeurs
                );


                header("Access-Control-Allow-Origin: *");
                header('Content-type: application/json');
                echo json_encode($courbe, JSON_FORCE_OBJECT);
            }
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "<br/>";
            die();
        }
    }

    //put your code here
}
