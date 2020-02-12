#ifndef TRAMEOREGON_H
#define TRAMEOREGON_H

#include "trame.h"
#include <QString>

class TrameOregon : public Trame
{
public:
    TrameOregon(const QJsonObject _jsonObject);
    TrameOregon();
    int getCanal() const;
    double getTemperature() const;
    int getHumidite() const;
    virtual QString getTrameAfficheur();
protected:
    int canal;
    double temperature;
    int humidite;
};

#endif // TRAMEOREGON_H
