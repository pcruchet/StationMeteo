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
    explicit Trame(const QJsonObject _jsonObject);
    Trame(const Trame &autre);
    int getIdStation() const;
    QDateTime getHorodatage() const;
    QString getBatterie() const;
    QString getModele() const;
    virtual QString getTrameAfficheur() = 0 ;

protected:
    int idStation;
    QDateTime horodatage;
    QString batterie;
    QString modele;
};

#endif // TRAME_H
