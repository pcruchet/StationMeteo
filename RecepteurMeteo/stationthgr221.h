#ifndef STATIONTHGR221_H
#define STATIONTHGR221_H

#include <QObject>
#include "trameoregon.h"
#include "accesbdd.h"

class StationTHGR221 : public QObject
{
    Q_OBJECT
public:
    explicit StationTHGR221(const int _idStation, AccesBDD &_bdd, QObject *parent = nullptr);
    void AjouterMesures(const TrameOregon _laTrame);
    bool EnregistrerMesures();

signals:
    void BatterieFaible(int station);

private:
    int idStation;
    double cumulTemperature;
    int cumulHumidite;
    int nbMesures;
    AccesBDD &bdd;
};

#endif // STATIONTHGR221_H
