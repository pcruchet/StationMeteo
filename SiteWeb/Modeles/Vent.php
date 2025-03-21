<?php

require_once ("ModeleBdd.php");

/**
 * Description of Vent
 *
 * @author philippe
 */
class Vent extends ModeleBdd {

    protected $distribution = [];
    protected $echelleBeaufort = ["&lt; 1 km/h", "1 à 5 km/h", "6 à 11 km/h", "12 à 19 km/h",
        "20 à 28 km/h", "29 à 38 km/h", "39 à 49 km/h", "50 à 61 km/h",
        "62 à 74 km/h", "75 à 88 km/h", "89 à 102 km/h",
        "103 à 117 km/h", "&gt; 118 km/h"];
    protected $directionsLettre = ["<b>Nord</b>", "NNE", "NE", "ENE", "<b>Est</b>",
        "ESE", "SE", "SSE", "<b>Sud</b>", "SSO", "SO",
        "OSO", "<b>Ouest</b>", "ONO", "NO", "NNO"];

    protected function ObtenirBeaufort($vitesse) {
        $intervaleVitesse = [1, 6, 12, 20, 29, 39, 50, 62, 75, 89, 103, 118];
        $beaufort = 0;
        for ($indice = 0; $beaufort == 0 && $indice < 11; $indice++) {
            if ($vitesse >= $intervaleVitesse[$indice] && $vitesse < $intervaleVitesse[$indice + 1])
                $beaufort = $indice + 1;
        }
        if ($vitesse >= $intervaleVitesse[11])
            $beaufort = 12;
        return $beaufort;
    }
    
    protected function ObtenirDirection($direction) {
        $intervaleDirection = [0,22.5,45,67.5,90,112.5,135,157.5,180,202.5,
                               225,247.5,270,292.5,315,337.5];
        
        $indiceDirection = 0 ;
        $trouve = false;
        for ($indice = 0; $trouve === false && $indice < 16; $indice++) {
            if ($direction === $intervaleDirection[$indice])
            {
                $indiceDirection = $indice;
                $trouve = true;
            }
            /*
            if($trouve === false && $direction < $intervaleDirection[$indice])
            {
                $indiceDirection = $indice-1;
                $trouve = true;
            }
             * 
             */
        }
        return $indiceDirection;
    }

    protected function FabriquerDistribution() {

        for ($beaufort = 0; $beaufort < 13; $beaufort++) {
            $this->distribution[$beaufort]['name'] = $this->echelleBeaufort[$beaufort];

            for ($indice = 0; $indice < 16; $indice++) {
                $this->distribution[$beaufort] ['data'][$indice] = 0; //$this->directionsLettre[$indice]
            }
        }
    }

    public function ObtenirDistributionVent($_dateDebut, $_dateFin) {
        try {
                        
            $debut = DateTime::createFromFormat("d/m/Y", $_dateDebut);
            $fin = DateTime::createFromFormat("d/m/Y", $_dateFin);
            date_time_set($debut, 0, 0);
            date_time_set($fin, 23, 59);
            
            
            $this->FabriquerDistribution();
            $this->Connexion();

            $requete = $this->_bdd->prepare("SELECT * FROM `Vent` WHERE  horodatage >= :dateDebut AND horodatage < :dateFin;");
            $requete->bindParam(":dateDebut", $debut->format("Y-m-d H:i"));
            $requete->bindParam(":dateFin", $fin->format("Y-m-d H:i"));
            $requete->execute() or die(print_r($requete->errorInfo()));
            $cpt = $requete->rowCount();
            while ($ligne = $requete->fetch()) {
                
                $vitesse = floatval($ligne['vitesse']);
                $direction = intval($ligne['direction']);
                $indiceVitesse = $this->ObtenirBeaufort($vitesse);
                $indiceDirection = $this->ObtenirDirection($direction);

                $this->distribution[$indiceVitesse]['data'][$indiceDirection] +=  1/$cpt*100 ;
            }
            
            header("Access-Control-Allow-Origin: *");
            header('Content-type: application/json');
            echo json_encode($this->distribution, JSON_FORCE_OBJECT);
            
        } catch (PDOException $ex) {
            print "Erreur !: " . $ex->getMessage() . "</br>";
            die();
        }
    }
}


