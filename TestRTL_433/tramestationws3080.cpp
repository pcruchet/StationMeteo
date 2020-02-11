#include "tramestationws3080.h"


TrameStationWS3080::TrameStationWS3080(QString _trame, QObject *parent) :
    QObject(parent)
{
    QJsonDocument doc = QJsonDocument::fromJson(_trame.toUtf8());
    QJsonObject jsonObject = doc.object();

    idStation = jsonObject.value(QString("id")).toInt();
    horodatage = QDateTime::fromString(jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));
    batterie = jsonObject.value(QString("battery")).toString();
    temperature = jsonObject.value(QString("temperature_C")).toDouble() ;
    humidite = jsonObject.value(QString("humidity")).toInt();
    vitesseDuVent = jsonObject.value(QString("speed")).toDouble();
    directionDuVent = jsonObject.value(QString("direction_deg")).toInt();
    vitesseRafale = jsonObject.value(QString("gust")).toDouble();
    pluie =  jsonObject.value(QString("rain")).toDouble();
}

int TrameStationWS3080::getIdStation() const
{
    return idStation;
}

QDateTime TrameStationWS3080::getHorodatage() const
{
    return horodatage;
}

QString TrameStationWS3080::getBatterie() const
{
    return batterie;
}

double TrameStationWS3080::getTemperature() const
{
    return temperature;
}

int TrameStationWS3080::getHumidite() const
{
    return humidite;
}

double TrameStationWS3080::getVitesseDuVent() const
{
    return vitesseDuVent;
}

int TrameStationWS3080::getDirectionDuVent() const
{
    return directionDuVent;
}

double TrameStationWS3080::getVitesseRafale() const
{
    return vitesseRafale;
}

double TrameStationWS3080::getPluie() const
{
    return pluie;
}
