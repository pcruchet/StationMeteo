#ifndef ACCESBDD_H
#define ACCESBDD_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include "temperaturehumidite.h"


class AccesBDD : public QObject
{
    Q_OBJECT
public:
    explicit AccesBDD(QObject *parent = nullptr);
    ~AccesBDD();
    void EnregistrerTemperatureHumidite(const int _idStation, const double _temperature, const int _humidite);

signals:

public slots:
private:
    QSqlDatabase bddMeteo;
};

#endif // ACCESBDD_H