#ifndef STATIONWS1080_H
#define STATIONWS1080_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include "tramews1080.h"
#include "accesbdd.h"
#include "pluie.h"

class StationWS1080 : public QObject
{
    Q_OBJECT
public:
    explicit StationWS1080(const int _idStation, AccesBDD &_bdd, QObject *parent = nullptr);
    int getNbMesures() const;

    void AjouterMesures(TrameWS1080 &_laTrame);
    bool EnregistrerMesures();


signals:
    void BatterieFaible(int station);

public slots:
private:  
    int idStation;
    QDateTime horodatage;
    QString batterie;
    QString nom;

    double cumulTemperature;
    int cumulHumidite;
    int nbMesures;

    int nbMesuresVent;
    double rafale;
    double cumulVitesseVent;
    QMap<int,int> direction;

    QDateTime debutPluie;
    Pluie cumulPluie;


    AccesBDD &bdd;
};

#endif // STATIONWS1080_H
