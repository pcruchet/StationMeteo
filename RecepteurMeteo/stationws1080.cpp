#include "stationws1080.h"
#include <QDebug>

StationWS1080::StationWS1080(const int _idStation,AccesBDD &_bdd, QObject *parent) :
    QObject(parent),
    idStation(_idStation),
    cumulTemperature(0),
    cumulHumidite(0),
    nbMesures(0),
    cumulPluie(-1),
    debutPluie(QDateTime::currentDateTime()),
    bdd(_bdd)
{

}

int StationWS1080::getNbMesures() const
{
    return nbMesures;
}

void StationWS1080::AjouterMesures(const TrameWS1080 _laTrame)
{
    cumulHumidite += _laTrame.getHumidite();
    cumulTemperature += _laTrame.getTemperature();
    if(cumulPluie > 0)
        cumulPluie += (_laTrame.getPluie() - anciennePluie);
    else
    {
        cumulPluie = 0;
        anciennePluie = _laTrame.getPluie();
    }
    nbMesures++;
}

bool StationWS1080::EnregistrerMesures()
{
    bool retour = false;
    if(nbMesures > 0)
    {
        QDateTime heureCourante(QDateTime::currentDateTime());
        if(QDateTime::currentDateTime().toMSecsSinceEpoch() - debutPluie.toMSecsSinceEpoch() > 60 * 60 * 1000)
        {

        }
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




