#include "trameoregon.h"

TrameOregon::TrameOregon(const int _idStationBdd, const QJsonObject _jsonObject):
    Trame (_idStationBdd,_jsonObject)
{
    canal       = _jsonObject.value(QString("channel")).toInt();
    temperature = _jsonObject.value(QString("temperature_C")).toDouble() ;
    humidite    = _jsonObject.value(QString("humidity")).toInt();
    batterie    = _jsonObject.value(QString("battery_ok")).toBool();
}

TrameOregon::TrameOregon():
    canal(0),
    temperature(0.0),
    humidite(0)
{
}

int TrameOregon::getCanal() const
{
    return canal;
}

double TrameOregon::getTemperature() const
{
    return temperature;
}

int TrameOregon::getHumidite() const
{
    return humidite;
}

QString TrameOregon::getTrameAfficheur()
{
    QString id  = QString::number(idStationBdd);
    QString tem = QString::number(temperature,'f',1);
    QString hum = QString::number(humidite);
    QString json = QString("{\"Station\":%1,\"Temperature\":%2,\"Humidite\":%3}").arg(id,tem,hum);
    return json;
}

bool TrameOregon::getBatterie() const
{
    return batterie;
}
