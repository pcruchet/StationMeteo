#ifndef STATION_H
#define STATION_H

#include <QDateTime>

#include "vent.h"
#include "temperaturehumidite.h"
#include "pluie.h"


class EchantillonMeteo : public TemperatureHumidite, Vent, Pluie
{
public:
    EchantillonMeteo(QString _trame);
    int getIdStation() const;
    QDateTime getHorodatage() const;
    QString getBatterie() const;
    QString getNom() const;
    TemperatureHumidite getTemperatureHumidite() const;
    Vent getVent() const;
    Pluie   getPluie() const;

private:
    int idStation;
    QDateTime horodatage;
    QString batterie;
    QString nom;
};

#endif // STATION_H
