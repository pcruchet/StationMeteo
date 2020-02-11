#ifndef ACCESBDD_H
#define ACCESBDD_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QDateTime>
#include "tramestationws3080.h"
#include "station.h"

class AccesBDD : public QObject
{
    Q_OBJECT
public:
    explicit AccesBDD(QObject *parent = nullptr);
    ~AccesBDD();
    void EnregistrerMeteo(TrameStationWS3080 _laTrame);
    void EnregistrerTemperatureHumidite(int _idStation, TemperatureHumidite _tempHum, QDateTime _horodatage);

signals:

public slots:
private:
    QSqlDatabase bddMeteo;
};

#endif // ACCESBDD_H
