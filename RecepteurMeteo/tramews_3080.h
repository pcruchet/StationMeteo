#ifndef TRAMEWS_3080_H
#define TRAMEWS_3080_H

#include <QJsonObject>
#include <QDateTime>


class TrameWS_3080
{
public:
    TrameWS_3080(const QJsonObject _jsonObject);
    int getIdStation() const;
    QDateTime getHorodatage() const;
    QString getBatterie() const;
    QString getNom() const;
    double getTemperature() const;
    int getHumidite() const;

private:
    int idStation;
    QDateTime horodatage;
    QString batterie;
    QString nom;
    double temperature;
    int humidite;
};

#endif // TRAMEWS_3080_H
