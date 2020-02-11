#include "tramews_3080.h"

TrameWS_3080::TrameWS_3080(const QJsonObject _jsonObject)
{
    idStation = _jsonObject.value(QString("id")).toInt();
    horodatage = QDateTime::fromString(_jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));
    batterie = _jsonObject.value(QString("battery")).toString();
    temperature = _jsonObject.value(QString("temperature_C")).toDouble() ;
    humidite = _jsonObject.value(QString("humidity")).toInt();
}

int TrameWS_3080::getIdStation() const
{
    return idStation;
}

QDateTime TrameWS_3080::getHorodatage() const
{
    return horodatage;
}

QString TrameWS_3080::getBatterie() const
{
    return batterie;
}

QString TrameWS_3080::getNom() const
{
    return nom;
}

double TrameWS_3080::getTemperature() const
{
    return temperature;
}

int TrameWS_3080::getHumidite() const
{
    return humidite;
}
