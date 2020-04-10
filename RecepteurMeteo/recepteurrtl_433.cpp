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
    int port = 7777;
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
    connect(leServeur,&ServeurMeteo::nouvelleConnexionClient,this,&RecepteurRTL_433::on_nouvelleConnexionClient);

    process = new QProcess(this);
    connect(process,&QProcess::readyReadStandardOutput,this,&RecepteurRTL_433::TraiterTrame);
    connect(process,&QProcess::errorOccurred,this,&RecepteurRTL_433::TraiterErreurProcess);

    timerBDD = new TimerProgramme(TimerProgramme::uneDemiHeure);
    connect(timerBDD,&QTimer::timeout,this,&RecepteurRTL_433::on_timeoutTimerBdd);

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
            if(it.value().secsTo(horodatage)>35) // une trame toutes les 58 secondes Extérieur 40 secondes serre
            {
                lesTramesDesStations.remove(idStation);
                trameValide = true;
            }
        }
        else  trameValide = true;

        if(trameValide)
        {
            if(idStation == idStationExterieure)
            {
                lesTramesDesStations.insert(idStation,horodatage);
                trameStation1 = TrameWS1080(STATION_1,jsonObject);
                stationExterieure.AjouterMesures(trameStation1);
                leServeur->EnvoyerMessageTexte(trameStation1.getTrameAfficheur());
            }
            else if (idStation == idStationSerre)
            {
                lesTramesDesStations.insert(idStation,horodatage);
                trameStation3 = TrameOregon(STATION_3,jsonObject);
                stationSerre.AjouterMesures(trameStation3);
                leServeur->EnvoyerMessageTexte(trameStation3.getTrameAfficheur());
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
    stationExterieure.EnregistrerMesures();
    stationSerre.EnregistrerMesures();
}


void RecepteurRTL_433::on_nouvelleConnexionClient()
{
    if(trameStation3.getIdStation() == STATION_3)
        leServeur->EnvoyerMessageTexte(trameStation3.getTrameAfficheur());
    if(trameStation1.getIdStation() == STATION_1)
        leServeur->EnvoyerMessageTexte(trameStation1.getTrameAfficheur());
}

void RecepteurRTL_433::on_batterieFaible(int _idStation)
{

}

