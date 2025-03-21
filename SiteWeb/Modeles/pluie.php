<?php
require_once("config.inc.php");

function connexionBD() {
    try 
    {
        $bdd = new PDO('mysql:host=' . SERVEURBD . ';dbname=' . NOMDELABASE, LOGIN, MOTDEPASSE);
    } 
    catch (Exception $ex) 
    {
        die('<br />Pb connexion serveur BD : ' . $ex->getMessage());
    }
    return $bdd;
}

function obtenirValeursPluieJSON($bdd) {
    
	
	$requete = $bdd->query("SELECT * FROM `Pluie`;");
	
	$valeurs = array();
	
	while ($ligne = $requete->fetch()) {		
		$date = new DateTime($ligne['horodatage']);
		$valeurs[$date->format('d-m-Y H:i')] = floatval($ligne['quantite']);			
	}
        
        $requete->closeCursor();
   
    header("Access-Control-Allow-Origin: *");
    header('Content-type: application/json');
    echo json_encode($valeurs, JSON_FORCE_OBJECT);       
}


	
obtenirValeursPluieJSON(connexionBD());
?>
