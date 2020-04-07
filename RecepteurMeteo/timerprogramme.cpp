#include "timerprogramme.h"
#include <QDebug>

/**
 * @brief TimerProgramme::TimerProgramme
 * @param _depart       heure de départ du timer
 * @param _msecDelai    interval entre deux timeout
 * @details Permet le lancement d'un QTimer à une date précise
 */
TimerProgramme::TimerProgramme(QDateTime _depart, int _msecDelai):
    msecDelai(_msecDelai)
{
    setSingleShot(true);
    setTimerType(Qt::PreciseTimer);
    connect(this,&QTimer::timeout,this,&TimerProgramme::SynchroniserDepart);
    start(static_cast<int>(QDateTime::currentDateTime().msecsTo(_depart)));
}

/**
 * @brief TimerProgramme::TimerProgramme
 * @param _msecDelai interval entre deux timeout
 * @details Déclenche un timer à une heure juste en fonction de _msecDelai
 *                  la valeur minimale de _msecDelai est la minute
 */
TimerProgramme::TimerProgramme(int _msecDelai):
    msecDelai(_msecDelai)
{
    setTimerType(Qt::PreciseTimer);
    QDateTime depart = QDateTime::currentDateTime();
    QTime heure = depart.time();
    QDate jour = depart.date();

    int temps = _msecDelai / 60 / 1000 ; // délai ramener en minutes

    if(temps < 60 && heure.minute() < (60 - temps))
        heure = QTime(heure.hour(),temps*(1 + (heure.minute() / temps))); // division entière
    else
    {
        if(heure.hour() < 23)
            heure = QTime(heure.hour()+1, 0);
        else
        {
            jour = jour.addDays(1);
            heure = QTime(0,0);
        }
    }
    depart = QDateTime(jour,heure);
    setSingleShot(true);
    connect(this,&QTimer::timeout,this,&TimerProgramme::SynchroniserDepart);
    start(static_cast<int>(QDateTime::currentDateTime().msecsTo(depart)));
    qDebug() << "Timer " << depart ;
}

/**
 * @brief TimerProgramme::SynchroniserDepart
 * @details Assure le déclenchement du timer à l'instant voulu
 */
void TimerProgramme::SynchroniserDepart()
{
    disconnect(this,&QTimer::timeout,this,&TimerProgramme::SynchroniserDepart);
    setSingleShot(false);
    start(msecDelai);
}
