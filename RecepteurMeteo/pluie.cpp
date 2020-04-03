#include "pluie.h"
#include <QDebug>

Pluie::Pluie(const int _periode):
    periode(_periode),
    ancienneValeur(-1)
{
    cumul.clear();
}

void Pluie::Ajouter(double _valeur)
{
    if(ancienneValeur >= 0) // négatif à la mise sous tension
    {
        if(_valeur >= ancienneValeur)
        {
            QDateTime maintenant(QDateTime::currentDateTime());
            qDebug() << maintenant;
            cumul.insert(maintenant,(_valeur - ancienneValeur));
            ancienneValeur = _valeur;
        }
    }
    else
    {
        ancienneValeur = _valeur;
    }
}

void Pluie::Purger()
{
    QDateTime maintenant(QDateTime::currentDateTime());
    QMap<QDateTime, double>::iterator it = cumul.begin() ;
    while( it != cumul.end() )
    {
        if( it.key().secsTo(maintenant) > periode )
            cumul.erase(it++);
        else
            ++it;
    }
}

double Pluie::ObtenirCumul(bool _purge)
{
    double sommeCumuls = 0;
    if(!cumul.isEmpty())
    {
        QDateTime maintenant(QDateTime::currentDateTime());
        QMap<QDateTime, double>::iterator it = cumul.begin() ;
        while( it != cumul.end() )
        {
            if( it.key().secsTo(maintenant) <= periode )
                sommeCumuls += it.value();
            ++it;
        }
        if(_purge)
            cumul.clear();
    }
    return sommeCumuls;
}
