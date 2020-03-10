#include "vent.h"
#include  <QtMath>

Vent::Vent(const double _vitesse, const int _direction, const double _rafale):
    vitesse(_vitesse),
    direction(_direction),
    rafale(_rafale)
{

}

bool Vent::operator==(const Vent &autre)
{
    return (qFabs(vitesse - autre.vitesse) <= 0.1 &&
            direction == autre.direction &&
            qFabs(rafale - autre.rafale) <= 0.1);
}
