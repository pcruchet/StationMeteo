#include "trame.h"

Trame::Trame()
{
    idStationBdd = 0;
    horodatage = QDateTime();
    batterie = "";
    modele = "" ;
}

Trame::Trame(const int _idStationBdd, const QJsonObject _jsonObject):
    idStationBdd(_idStationBdd)
{
    horodatage  = QDateTime::fromString(_jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));
    modele      = _jsonObject.value(QString("model")).toString();
}

Trame::Trame(const Trame &autre)
{
    idStationBdd = autre.idStationBdd;
    horodatage = autre.horodatage;
    modele = autre.modele;
}

int Trame::getIdStation() const
{
    return idStationBdd;
}

QDateTime Trame::getHorodatage() const
{
    return horodatage;
}

QString Trame::getModele() const
{
    return modele;
}

Trame::~Trame()
{

}
