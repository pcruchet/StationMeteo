#ifndef TIMERPROGRAMME_H
#define TIMERPROGRAMME_H

#include <QTimer>
#include <QDateTime>

/**
 * @brief The TimerProgramme class
 * @details Ce timer hérité de QTimer peit être déclenchée à une heure et une date précise
 */
class TimerProgramme : public QTimer
{
public:
    enum DUREE
    {
        uneHeure = 36000000,
        uneDemiHeure = 1800000,
        quinzeMinutes = 900000,
        dixMinutes = 600000,
        cinqMinutes = 300000
    };

    TimerProgramme(QDateTime _depart, int _msecDelai);
    TimerProgramme(int _msecDelai);
private slots:
    void SynchroniserDepart();
private:
    int msecDelai;      /// Delai en millisecondes pour le timer
};

#endif // TIMERPROGRAMME_H
