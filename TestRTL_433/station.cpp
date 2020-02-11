#include "station.h"

#include <QJsonDocument>
#include <QJsonObject>

EchantillonMeteo::EchantillonMeteo(QString _trame)
{
    QJsonDocument doc = QJsonDocument::fromJson(_trame.toUtf8());
    QJsonObject jsonObject = doc.object();

    idStation = jsonObject.value(QString("id")).toInt();
    horodatage = QDateTime::fromString(jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));
    batterie = jsonObject.value(QString("battery")).toString();
    temperature = jsonObject.value(QString("temperature_C")).toDouble() ;
    humidite = jsonObject.value(QString("humidity")).toDouble();
    vitesseDuVent = jsonObject.value(QString("speed")).toDouble();
    directionDuVent = jsonObject.value(QString("direction_deg")).toInt();
    vitesseRafale = jsonObject.value(QString("gust")).toDouble();
    quantite =  jsonObject.value(QString("rain")).toDouble();
}

int EchantillonMeteo::getIdStation() const
{
    return idStation;
}

QDateTime EchantillonMeteo::getHorodatage() const
{
    return horodatage;
}

QString EchantillonMeteo::getBatterie() const
{
    return batterie;
}

QString EchantillonMeteo::getNom() const
{
    return nom;
}

TemperatureHumidite EchantillonMeteo::getTemperatureHumidite() const
{
    return  TemperatureHumidite(temperature,humidite);
}

Vent EchantillonMeteo::getVent() const
{
    return Vent(vitesseDuVent, directionDuVent, vitesseRafale);
}

Pluie EchantillonMeteo::getPluie() const
{
    return Pluie(quantite);
}
