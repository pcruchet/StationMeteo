#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "recepteurrtl_433.h"
#include "tramews_1080.h"
#include "trameoregon.h"



/**
 * @brief RecepteurRTL_433::RecepteurRTL_433
 * @param parent
 * @details Constructeur de la classe
 */
RecepteurRTL_433::RecepteurRTL_433(QObject *parent) :
    QObject(parent),
    process(nullptr),
    stationDeLaSerre(71,laBdd),
    leServeur(7777)
{
    process = new QProcess(this);
    connect(process,&QProcess::readyReadStandardOutput,this,&RecepteurRTL_433::TraiterTrame);
    connect(&timerBDD,&QTimer::timeout,this,&RecepteurRTL_433::on_timeoutTimerBdd);

    timerBDD.start(15*60*1000); // enregistrement toutes les 15 minutes

}

/**
 * @brief RecepteurRTL_433::~RecepteurRTL_433
 * @details Destructeur de la classe
 */
RecepteurRTL_433::~RecepteurRTL_433()
{
    if(process != nullptr)
        delete process;
}

/**
 * @brief RecepteurRTL_433::LancerEcoute
 * @details Lance le processus d'écoute du RTL_433
 */
void RecepteurRTL_433::LancerEcoute()
{
    QStringList arguments;
    arguments << "-R" << "32" << "-R" << "12" << "-F" << "json";
    if(!process->isTransactionStarted())
        process->start("/home/philippe/StationMeteo/build-rtl_433-Desktop_Qt_5_12_1_GCC_64bit-Du00e9faut/src/rtl_433",arguments);
}

/**
 * @brief RecepteurRTL_433::TraiterTrame
 * @details Traite la trame json en provenance du circuit RTL_433
 */
void RecepteurRTL_433::TraiterTrame()
{
    QByteArray sortieStandard = process->readAllStandardOutput();
    TrameWS1080 trameStation1;
    TrameOregon trameStation3;



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
            lesTramesDesStations.insert(idStation,horodatage);
            switch (idStation)
            {
            case STATION_1:
                trameStation1 = TrameWS1080(jsonObject);
                leServeur.processTextMessage(trameStation1.getTrameAfficheur());
                //stationDeLaSerre.AjouterMesures(laTrame);
                break;
            case STATION_3:
                trameStation3 = TrameOregon(jsonObject);
                leServeur.processTextMessage(trameStation3.getTrameAfficheur());
                break;
            }
        }



        trameCourante.clear();
    }
}

void RecepteurRTL_433::on_timeoutTimerBdd()
{
    stationDeLaSerre.EnregistrerMesures();
}
