#ifndef VENT_H
#define VENT_H


class Vent
{
public:
    Vent(const double _vitesse, const int _direction, const double _rafale);
    bool operator==(const Vent &autre) ;
protected:
    double vitesse;
    int    direction;
    double rafale;
    int    nbMesures;
};

#endif // VENT_H
