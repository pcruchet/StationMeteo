#ifndef TRAMEWS_3080_H
#define TRAMEWS_3080_H

#include "trame.h"


class TrameWS1080: public Trame
{
public:
    TrameWS1080(const int _idStationBdd, const QJsonObject _jsonObject);
    TrameWS1080();
    TrameWS1080(const TrameWS1080 &autre);
    double getTemperature() const;
    int getHumidite() const;
    int getDirectionVent() const;
    double getVitesseVent() const;
    double getRafale() const;
    double getPluie() const;
    QString getTrameAfficheur();

protected:
    double temperature;
    int humidite;
    int directionVent;
    double vitesseVent;
    double rafale;
    double pluie;
};

#endif // TRAMEWS_3080_H
