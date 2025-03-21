<?php

/**
 * Description of ModeleBdd
 *
 * @author philippe
 */
require_once("config.inc.php");

class ModeleBdd {

    protected $_bdd;

    public function Connexion() {
        try {
            $this->_bdd = new PDO('mysql:host=' . SERVEURBD . ';dbname=' . NOMDELABASE, LOGIN, MOTDEPASSE);
        } catch (Exception $ex) {
            die('<br />Pb connexion serveur BD : ' . $ex->getMessage());
        }
    }

}
