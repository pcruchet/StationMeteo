#include "stationws1080.h"

StationWS1080::StationWS1080(const int _idStation,AccesBDD &_bdd, QObject *parent) :
    QObject(parent),
    idStation(_idStation),
    cumulTemperature(0),
    cumulHumidite(0),
    nbMesures(0),
    bdd(_bdd)
{
}

int StationWS1080::getNbMesures() const
{
    return nbMesures;
}

void StationWS1080::AjouterMesures(const TrameWS1080 _laTrame)
{
    if(_laTrame.getBatterie() != "OK")
        emit BatterieFaible(idStation);
    cumulHumidite += _laTrame.getHumidite();
    cumulTemperature += _laTrame.getTemperature();
    nbMesures++;
}

bool StationWS1080::EnregistrerMesures()
{
    bool retour = false;
    if(nbMesures > 0)
    {
        double latemperture = cumulTemperature / static_cast<double>(nbMesures);
        int lHumidite = cumulHumidite / nbMesures ;
        bdd.EnregistrerTemperatureHumidite(idStation,latemperture,lHumidite);
        cumulHumidite=0;
        cumulTemperature=0;
        nbMesures = 0;      
        retour = true;
     }
    return retour;
}




