#ifndef VENT_H
#define VENT_H


class Vent
{

public:
    explicit Vent();
    Vent(double _vitesse, int _direction, double _rafale);

protected:
    double vitesseDuVent;
    int directionDuVent;
    double vitesseRafale;
};



#endif // VENT_H
