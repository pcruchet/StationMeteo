#include "trame.h"

Trame::Trame()
{
    idStation = 0;
    horodatage = QDateTime();
    batterie = "";
    modele = "" ;
}

Trame::Trame(const QJsonObject _jsonObject)
{
    idStation   = _jsonObject.value(QString("id")).toInt();
    horodatage  = QDateTime::fromString(_jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));
    batterie    = _jsonObject.value(QString("battery")).toString();
    modele      = _jsonObject.value(QString("model")).toString();

}

Trame::Trame(const Trame &autre)
{
    idStation = autre.idStation;
    horodatage = autre.horodatage;
    batterie = autre.batterie;
    modele = autre.modele;
}

int Trame::getIdStation() const
{
    return idStation;
}

QDateTime Trame::getHorodatage() const
{
    return horodatage;
}

QString Trame::getBatterie() const
{
    return batterie;
}

QString Trame::getModele() const
{
    return modele;
}
