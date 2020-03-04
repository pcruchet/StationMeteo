#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "recepteurrtl_433.h"
#include "tramews1080.h"
#include "trameoregon.h"



/**
 * @brief RecepteurRTL_433::RecepteurRTL_433
 * @param parent
 * @details Constructeur de la classe
 */
RecepteurRTL_433::RecepteurRTL_433(QObject *parent) :
    QObject(parent),
    process(nullptr),
    leServeur(nullptr),
    stationExterieure(STATION_1,laBdd),
    stationSerre(STATION_3,laBdd),
    bddSerre(false)
{
    int port;
    QFileInfo testFichier("config.ini");
    if(testFichier.exists() && testFichier.isFile())
    {
        qDebug() << "FichierIni Ok";
        QSettings initialisation("config.ini",QSettings::IniFormat);

        commande = initialisation.value("Recepteur/commande","/home/pi/StationMeteo/build-rtl_433-Desktop-Defaut/src/rtl_433").toString();
        port = initialisation.value("ServeurMeteo/port",7777).toInt();
        idStationExterieure = initialisation.value("Station1/id",71).toInt();
        idStationSerre = initialisation.value("Station2/id",154).toInt();
        delaiBdd = initialisation.value("ServeurMeteo/delai",15).toInt();
    }

    leServeur = new ServeurMeteo(static_cast<quint16>(port));
    process = new QProcess(this);

    connect(process,&QProcess::readyReadStandardOutput,this,&RecepteurRTL_433::TraiterTrame);
    connect(process,&QProcess::errorOccurred,this,&RecepteurRTL_433::TraiterErreurProcess);
    connect(&timerBDD,&QTimer::timeout,this,&RecepteurRTL_433::on_timeoutTimerBdd);

    timerBDD.start(delaiBdd*60*1000);

}

/**
 * @brief RecepteurRTL_433::~RecepteurRTL_433
 * @details Destructeur de la classe
 */
RecepteurRTL_433::~RecepteurRTL_433()
{
    if(process != nullptr)
        delete process;
    if(leServeur != nullptr)
        delete leServeur;
}

/**
 * @brief RecepteurRTL_433::LancerEcoute
 * @details Lance le processus d'écoute du RTL_433
 *          pour capteur Oregon et Fine Offset Electronics
 *          Les trames reçues seront au format Json
 */
void RecepteurRTL_433::LancerEcoute()
{
    qDebug() << "LancerEcoute";
    QStringList arguments;
    arguments << "-R" << "32" << "-R" << "12" << "-F" << "json";
    if(!process->isTransactionStarted())
        process->start(commande,arguments);
}

/**
 * @brief RecepteurRTL_433::TraiterTrame
 * @details Traite la trame json en provenance du circuit RTL_433
 */
void RecepteurRTL_433::TraiterTrame()
{
    //qDebug() << "TraiterTrame";
    QByteArray sortieStandard = process->readAllStandardOutput();
    int indice = 0;
    while(sortieStandard[indice] != '}' && indice < sortieStandard.count())
    {
        trameCourante += sortieStandard[indice++];
    }

    if(sortieStandard[indice] == '}')
    {
        trameCourante += "}";
        if(trameCourante.at(0)== '"')
            trameCourante.remove(0,1);

        QJsonDocument doc = QJsonDocument::fromJson(trameCourante.toUtf8());
        trameCourante.clear();

        QJsonObject jsonObject = doc.object();
        int idStation = jsonObject.value(QString("id")).toInt();
        QDateTime horodatage = QDateTime::fromString(jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));

        bool trameValide = false;

        QMultiMap<int,QDateTime>::iterator it = lesTramesDesStations.find(idStation);
        if (it != lesTramesDesStations.end())
        {
            if(it.value().secsTo(horodatage)>50) // une trame toutes les 58 secondes
            {
                lesTramesDesStations.remove(idStation);
                trameValide = true;
            }
        }
        else  trameValide = true;

        if(trameValide)
        {
            TrameWS1080 trameStation1;
            TrameOregon trameStation3;

            if(idStation == idStationExterieure)
            {
                lesTramesDesStations.insert(idStation,horodatage);
                trameStation1 = TrameWS1080(STATION_1,jsonObject);
                leServeur->EnvoyerMessageTexte(trameStation1.getTrameAfficheur());
                stationExterieure.AjouterMesures(trameStation1);
            }
            else if (idStation == idStationSerre)
            {
                lesTramesDesStations.insert(idStation,horodatage);
                trameStation3 = TrameOregon(STATION_3,jsonObject);
                leServeur->EnvoyerMessageTexte(trameStation3.getTrameAfficheur());
                stationSerre.AjouterMesures(trameStation3);
            }
        }
    }
}

void RecepteurRTL_433::TraiterErreurProcess(QProcess::ProcessError _erreur)
{
    qDebug() << "Erreur du process " << commande << " Erreur " << _erreur;
}

void RecepteurRTL_433::on_timeoutTimerBdd()
{
    if(bddSerre)
    {
        stationSerre.EnregistrerMesures();
        bddSerre = false;
    }
    else
    {
        stationExterieure.EnregistrerMesures();
        bddSerre = true;
    }

}
