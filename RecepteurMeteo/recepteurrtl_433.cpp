#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "recepteurrtl_433.h"
#include "tramews_3080.h"



/**
 * @brief RecepteurRTL_433::RecepteurRTL_433
 * @param parent
 * @details Constructeur de la classe
 */
RecepteurRTL_433::RecepteurRTL_433(QObject *parent) :
    QObject(parent),
    process(nullptr),
    stationDeLaSerre(71,laBdd)
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
    arguments << "-R" << "32" << "-F" << "json";
    if(!process->isTransactionStarted())
        process->start("rtl_433",arguments);
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
        QJsonObject jsonObject = doc.object();
        int idStation = jsonObject.value(QString("id")).toInt();
        QDateTime horodatage = QDateTime::fromString(jsonObject.value(QString("time")).toString(),QString("yyyy-MM-dd hh:mm:ss"));

        bool trameValide = false;
        QMultiMap<int,QDateTime>::iterator it = lesTramesDesStations.find(idStation);
        if (it != lesTramesDesStations.end())
        {
            if(horodatage.secsTo(it.value())>50) // une trame toutes les 58 secondes
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
                TrameWS_3080 laTrame(jsonObject);
                stationDeLaSerre.AjouterMesures(laTrame);
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
