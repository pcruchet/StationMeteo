#ifndef TEMPERATUREHUMIDITE_H
#define TEMPERATUREHUMIDITE_H


#include <QDateTime>

class TemperatureHumidite
{

public:
    explicit TemperatureHumidite();
    TemperatureHumidite(double _temperature, int _humidite);
    bool operator==(const TemperatureHumidite &autre) ;
    void operator+=(const TemperatureHumidite &autre);

    TemperatureHumidite ObtenirValeurMoyenne() ;

    double getTemperature() const;
    int getHumidite() const;

protected:
    double temperature;
    int humidite;
    int nbMesures;

};

#endif // TEMPERATUREHUMIDITE_H
