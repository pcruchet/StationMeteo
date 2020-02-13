#include "stationthgr221.h"

StationTHGR221::StationTHGR221(const int _idStation, AccesBDD &_bdd, QObject *parent) :
    QObject(parent),
    idStation(_idStation),
    nbMesures(0),
    bdd(_bdd)
{
}

void StationTHGR221::AjouterMesures(const TrameOregon _laTrame)
{
    if(_laTrame.getBatterie() != "OK")
        emit BatterieFaible(idStation);
    cumulHumidite += _laTrame.getHumidite();
    cumulTemperature += _laTrame.getTemperature();
    nbMesures++;
}

bool StationTHGR221::EnregistrerMesures()
{
    bool retour = false;
    if(nbMesures > 0)
    {
        double latemperture = cumulTemperature / static_cast<double>(nbMesures);
        int lHumidite = cumulHumidite / nbMesures ;
        bdd.EnregistrerTemperatureHumidite(idStation,latemperture,lHumidite);

        retour = true;
        nbMesures = 0;

    }
    return retour;
}
