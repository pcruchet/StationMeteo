#ifndef RECEPTEURRTL_433_H
#define RECEPTEURRTL_433_H

#include <QObject>
#include <QProcess>
#include <QDateTime>
#include <QMap>
#include <QTimer>

#include "stationws1080.h"
#include "stationthgr221.h"
#include "serveurmeteo.h"
#include "timerprogramme.h"

enum STATION
{
    STATION_1 = 71,     // Station Extérieure
    STATION_2 = 161,    // Capteur des voisins
    STATION_3 = 169     // Capteur de la serre
};

class RecepteurRTL_433 : public QObject
{
    Q_OBJECT
public:
    explicit RecepteurRTL_433(QObject *parent = nullptr);
    ~RecepteurRTL_433();
    void LancerEcoute();
signals:

private slots:
    void TraiterTrame();
    void TraiterErreurProcess(QProcess::ProcessError _erreur);
    void on_timeoutTimerBdd();
    void on_timeoutTimerPluie();
    void on_nouvelleConnexionClient();
    void on_batterieFaible(int _idStation);

private:
    QProcess *process;
    QString trameCourante;
    QMultiMap <int, QDateTime> lesTramesDesStations;
    TimerProgramme *timerBDD;
    TimerProgramme *timerPluie;
    AccesBDD laBdd;
    QString commande;

    ServeurMeteo *leServeur;

    StationWS1080 stationExterieure;
    StationTHGR221 stationSerre;

    TrameWS1080 trameStation1;
    TrameOregon trameStation3;

    int idStationExterieure;
    int idStationSerre;
    int delaiBdd;
    bool bddSerre;
};

#endif // RECEPTEURRTL_433_H
