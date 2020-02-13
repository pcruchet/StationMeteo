#ifndef VENT_H
#define VENT_H


class Vent
{
public:
    Vent(const double _vitesse, const int _direction, const double _rafale);
protected:
    double vitesse;
    double rafale;
    int    direction;
    int    nbMesures;
};

#endif // VENT_H
