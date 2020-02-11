#ifndef TRAMESTATIONWS3080_H
#define TRAMESTATIONWS3080_H

#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class TrameStationWS3080 : public QObject
{
    Q_OBJECT
public:
    explicit TrameStationWS3080(QString _trame, QObject *parent = nullptr);

    int getIdStation() const;
    QDateTime getHorodatage() const;
    QString getBatterie() const;
    double getTemperature() const;
    int getHumidite() const;
    double getVitesseDuVent() const;
    int getDirectionDuVent() const;
    double getVitesseRafale() const;
    double getPluie() const;

signals:

public slots:
private:
    int idStation;
    QDateTime horodatage;
    QString batterie;
    double temperature;
    int humidite;
    double vitesseDuVent;
    int directionDuVent;
    double vitesseRafale;
    double pluie;
};

#endif // TRAMESTATIONWS3080_H
