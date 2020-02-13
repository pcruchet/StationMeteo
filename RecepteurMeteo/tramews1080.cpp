#include "tramews1080.h"

TrameWS1080::TrameWS1080(const QJsonObject _jsonObject):
    Trame (_jsonObject)
{
    temperature = _jsonObject.value(QString("temperature_C")).toDouble() ;
    humidite    = _jsonObject.value(QString("humidity")).toInt();
    directionVent = _jsonObject.value(QString("wind_dir_deg")).toInt();
    vitesseVent = _jsonObject.value(QString("wind_avg_km_h")).toDouble() ;
    rafale = _jsonObject.value(QString("wind_max_km_h")).toDouble() ;
    pluie = _jsonObject.value(QString("rain_mm")).toDouble() ;
}

TrameWS1080::TrameWS1080() :
    temperature(0.0),
    humidite(0),
    directionVent(0),
    vitesseVent(0.0),
    rafale(0.0),
    pluie(0)
{
}

TrameWS1080::TrameWS1080(const TrameWS1080 &autre):
    Trame ()
{
    idStation = autre.idStation;
    horodatage = autre.horodatage;
    batterie = autre.batterie;
    modele = autre.modele;
    temperature = autre.temperature;
    humidite = autre.humidite;
    directionVent = autre.directionVent;
    vitesseVent = autre.vitesseVent;
    rafale = autre.rafale;
    pluie = autre.pluie;
}

double TrameWS1080::getTemperature() const
{
    return temperature;
}

int TrameWS1080::getHumidite() const
{
    return humidite;
}

int TrameWS1080::getDirectionVent() const
{
    return directionVent;
}

double TrameWS1080::getVitesseVent() const
{
    return vitesseVent;
}

double TrameWS1080::getRafale() const
{
    return rafale;
}

double TrameWS1080::getPluie() const
{
    return pluie;
}

QString TrameWS1080::getTrameAfficheur()
{
    QString id  = QString::number(idStation);
    QString tem = QString::number(temperature,'f',1);
    QString hum = QString::number(humidite);
    QString plu = QString::number(pluie);
    QString dir = QString::number(directionVent);
    QString vit = QString::number(vitesseVent,'f',1);
    QString raf = QString::number(rafale,'f',1);

    QString json = QString("{\"Station\":%1,\"Temperature\":%2,").arg(id,tem);
    json += QString("\"Humidite\":%1,\"Pluie\":%2,\"Direction\":%3,").arg(hum,plu,dir);
    json += QString("\"Vitesse\":%1,\"Rafale\":%2}").arg(vit,raf);

    return json;
}
