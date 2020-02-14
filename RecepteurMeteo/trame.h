#ifndef TRAME_H
#define TRAME_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QJsonObject>

class Trame
{
public:
    Trame();
    explicit Trame(const int _idStationBdd, const QJsonObject _jsonObject);
    Trame(const Trame &autre);
    int getIdStation() const;
    QDateTime getHorodatage() const;
    QString getModele() const;
    virtual QString getTrameAfficheur() = 0 ;
    virtual ~Trame();

protected:
    int idStationBdd;
    QDateTime horodatage;
    QString modele;
};

#endif // TRAME_H
