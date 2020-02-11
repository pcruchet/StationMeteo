#include "temperaturehumidite.h"
#include  <QtMath>

TemperatureHumidite::TemperatureHumidite()
{
    nbMesures=0;
}

TemperatureHumidite::TemperatureHumidite(double _temperature, int _humidite):
    temperature(_temperature),
    humidite(_humidite)
{
    nbMesures = 0;
}

bool TemperatureHumidite::operator==(const TemperatureHumidite &autre)
{
    return (qFabs(temperature - autre.temperature) <= 0.1 && humidite == autre.humidite);
}

void TemperatureHumidite::operator+=(const TemperatureHumidite &autre)
{
    temperature += autre.temperature;
    humidite += autre.humidite;
    nbMesures++;
}

TemperatureHumidite TemperatureHumidite::ObtenirValeurMoyenne()
{
    double temperatureMoyenne = 0;
    int    humiditeMoyenne = -1 ;
    if(nbMesures > 0)
    {
        temperatureMoyenne = temperature / (float)nbMesures;
        humiditeMoyenne = humidite / nbMesures;
        nbMesures = 0;
        temperature = 0;
        humidite = 0;
    }
    return TemperatureHumidite(temperatureMoyenne,humiditeMoyenne);
}

double TemperatureHumidite::getTemperature() const
{
    return temperature;
}

int TemperatureHumidite::getHumidite() const
{
    return humidite;
}
