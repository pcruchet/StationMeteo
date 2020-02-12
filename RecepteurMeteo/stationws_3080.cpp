#include "stationws_3080.h"

StationWS_3080::StationWS_3080(const int _idStation,AccesBDD &_bdd, QObject *parent) :
    QObject(parent),
    idStation(_idStation),
    nbMesures(0),
    bdd(_bdd)
{
}

int StationWS_3080::getIdStation() const
{
   return idStation;
}

QDateTime StationWS_3080::getHorodatage() const
{
    return horodatage;
}

QString StationWS_3080::getBatterie() const
{
    return batterie;
}

QString StationWS_3080::getNom() const
{
    return nom;
}

int StationWS_3080::getNbMesures() const
{
    return nbMesures;
}

void StationWS_3080::AjouterMesures(const TrameWS1080 _laTrame)
{
    if(_laTrame.getBatterie() != "OK")
        emit BatterieFaible(idStation);
    cumulHumidite += _laTrame.getHumidite();
    cumulTemperature += _laTrame.getTemperature();
    nbMesures++;
}

bool StationWS_3080::EnregistrerMesures()
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




