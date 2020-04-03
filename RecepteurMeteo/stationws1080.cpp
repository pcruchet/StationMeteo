#include "stationws1080.h"
#include "sleeperthread.h"
#include <QDebug>

StationWS1080::StationWS1080(const int _idStation,AccesBDD &_bdd, QObject *parent) :
    QObject(parent),
    idStation(_idStation),
    cumulTemperature(0),
    cumulHumidite(0),
    nbMesures(0),
    nbMesuresVent(0),
    rafale(0),
    cumulVitesseVent(0),
    debutPluie(QDateTime::currentDateTime()),
    bdd(_bdd)
{
    direction.clear();
}

int StationWS1080::getNbMesures() const
{
    return nbMesures;
}

void StationWS1080::AjouterMesures(TrameWS1080 &_laTrame)
{
    cumulHumidite += _laTrame.getHumidite();
    cumulTemperature += _laTrame.getTemperature();
    nbMesures++;

    if(rafale < _laTrame.getRafale())
        rafale = _laTrame.getRafale();
    if(_laTrame.getVitesseVent() > 1 )
    {
        cumulVitesseVent += _laTrame.getVitesseVent();
        QMap<int,int>::iterator itDirection = direction.find(_laTrame.getDirectionVent());
        if(itDirection == direction.end())
            direction.insert(_laTrame.getDirectionVent(),1);     //initialisation du compteur
        else
            itDirection.value() += 1;
        nbMesuresVent++;
    }

    cumulPluie.Ajouter(_laTrame.getPluie());
    _laTrame.setPluie(cumulPluie.ObtenirCumul(false));

}

bool StationWS1080::EnregistrerTemperatureHumiditeVent()
{
    bool retour = false;
    if(nbMesures > 0)
    {
        // Température - himidité
        double latemperture = cumulTemperature / static_cast<double>(nbMesures);
        int lHumidite = cumulHumidite / nbMesures ;
        int compteur=0;
        while(compteur < 3 && !bdd.EnregistrerTemperatureHumidite(idStation,latemperture,lHumidite))
        {
            SleeperThread::msleep(400);     // attente de la fin des écritures dans la bdd
            qDebug() << ++compteur;
        }
        cumulHumidite=0;
        cumulTemperature=0;

        // enregistrement du vent
        if(nbMesuresVent > 0)
        {
            int valeurMaxi = 0;
            QMap<int,int>::iterator itDirectionMax;
            for(QMap<int,int>::iterator itDirection = direction.begin(); itDirection != direction.end();itDirection++)
            {
                if(itDirection.value()>valeurMaxi)
                {
                    valeurMaxi = itDirection.value();
                    itDirectionMax = itDirection;
                }
            }

            bdd.EnregistrerVent(idStation,cumulVitesseVent/static_cast<double>(nbMesuresVent),itDirectionMax.key(),rafale);
            rafale = 0;
            cumulVitesseVent = 0;
            direction.clear();
            nbMesuresVent = 0;
        }
        nbMesures = 0;
        retour = true;
    }
    return retour;
}

void StationWS1080::EnregistrerPluie()
{
    qDebug() << "EnregistrerPluie ";
    double quantite = cumulPluie.ObtenirCumul();
    int compteur=0;
    while(compteur < 3 &&  !bdd.EnregistrerPluie(idStation,quantite))
    {
        SleeperThread::msleep(400);
        qDebug() << ++compteur;
    }
}




