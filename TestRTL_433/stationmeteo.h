#ifndef STATIONMETEO_H
#define STATIONMETEO_H

#include <QObject>
#include <QDateTime>
#include <QProcess>
#include <QTimer>
#include "temperaturehumidite.h"
#include "vent.h"
#include "pluie.h"
#include "accesbdd.h"
#include "serveurmeteo.h"

class StationMeteo : public QObject
{
    Q_OBJECT
public:
    explicit  StationMeteo(QProcess *_processus, AccesBDD &_laBdd, QObject *parent = nullptr);
    void      TraiterTrameMeteo();
    int       getIdStation() const;
    QDateTime getHorodatage() const;
    QString   getBatterie() const;
    void      OnTimeOutTimerMajBdd();

signals:
    void      DonneesStationDisponible();
public slots:
private:
    QProcess    *processus;
    QString     trameCourante ;
    int         idStation;
    QDateTime   horodatage;
    QDateTime   horodatagePrec;
    QString     batterie;

    TemperatureHumidite temperatureHumidite;
    Vent vent;
    Pluie pluie;

    TemperatureHumidite cumulTemperatureHumidite;
    QTimer timerMajBdd;
    AccesBDD &laBdd;
    ServeurMeteo leServeur;

};

#endif // STATIONMETEO_H
