<?php ?>

<div class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">

    <div class="btn-group">
        <button type="button" class="btn btn-dark dropdown-toggle" data-toggle="dropdown">
            Météo du jardin
        </button>
        <div class="dropdown-menu" style="z-index: 1">
            <a class="dropdown-item" href="Vues/Php/pageTemperatureHumidite.php">Température et Humidité</a>
            <a class="dropdown-item" href="Vues/Php/pagePluie.php">Cumul de pluie</a>
            <a class="dropdown-item" href="Vues/Php/pageVent.php">Vent</a>
            <a class="dropdown-item" href="Vues/Php/pageTableau.php">Tableau</a>
        </div>
    </div>
    <button type="button" class="btn btn-dark">Contrôle de la serre</button>
    <button type="button" class="btn btn-dark">Paramètrage</button>
</div>
