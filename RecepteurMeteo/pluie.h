#ifndef PLUIE_H
#define PLUIE_H
#include <QMap>
#include <QDateTime>

class Pluie
{
public:
    Pluie(const int _periode=3600); // 3600 s pour 1 h
    void Ajouter(double _valeur);
    void Purger();
    double ObtenirCumul(bool _purge=true);
private:
    QMap <QDateTime,double> cumul;
    int periode;
    double ancienneValeur;
};

#endif // PLUIE_H
