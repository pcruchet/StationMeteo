function obtenirDirectionDuVent(valeur) {
    var directionDegre = [0,22.5,45,67.5,90,112.5,135,157.5,180,202.5,225,247.5,270,292.5,315,337.5];
    var directionTexte = ["N","NNE","NE","ENE","E","ESE","SE","SSE","S","SSO","SO","OSO","O","ONO","NO","NNO"]
    var direction = Number.parseFloat(valeur);

    var indice = 0;
    var trouve = false;
    while(trouve === false && indice < 16)
    {
        if(directionDegre[indice] === valeur)
        {
            trouve = true;
        }
        else
        {
            indice++;
        }
    }
    var retour = "Inconnu"
    if(trouve === true)
    {
        retour = directionTexte[indice];
    }

    return retour;

}
