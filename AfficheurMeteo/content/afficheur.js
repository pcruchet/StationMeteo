function ajouterPoint(valeur) {
    var leTexte = ".";
    leTexte += valeur;
    return leTexte;
}

function obtenirTemperature(valeur) {
    return Math.trunc(valeur);
}

function obtenirDixieme(valeur) {
    var nombre = Number.parseFloat(valeur - Math.trunc(valeur)).toFixed(1);
    return(nombre*10);
}
