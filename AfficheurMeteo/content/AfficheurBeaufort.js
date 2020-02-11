function obtenirBeaufort(valeur){
    var intervalVitesse = [1,5,11,19,28,38,50,62,75,89,103,117];

    var vitesse = Number.parseFloat(valeur * 60 * 60) / Number.parseFloat(1000);

    var beaufort = 0;
    for(var i=0 ; i<11 ; i++)
    {
        if(vitesse >= intervalVitesse[i] && vitesse < intervalVitesse[i+1] )
            beaufort = i+1;
    }

    if(vitesse >= intervalVitesse[11])
        beaufort = 12;

    return beaufort;
}

function obtenirAppelationVent(valeur){
    var appelation = ["calme","brise très legère","brise legère","petite brise",
                      "jolie brise","bonne brise","vent frais","grand vent","coup de vent",
                      "fort coup de vent","tempête","violente tempête", "ouragan"];

    console.log(valeur);
    return appelation[valeur];
}

function afficherEchelleBeaufort(valeur,couleur)
{
    for(var i=0 ;i < valeur ;i++)
    {
        afficheurBeaufort.echelleBeaufort.itemAt(i).color = couleur
    }
}
