#include "stationmeteo.h"
#include "tramestationws3080.h"

#include <QDebug>

StationMeteo::StationMeteo(QProcess *_processus, AccesBDD &_laBdd, QObject *parent) :
    QObject(parent),
    processus(_processus),
    cumulTemperatureHumidite(TemperatureHumidite(0,0)),
    laBdd(_laBdd),
    leServeur(7777,this)


{

    connect(&timerMajBdd,&QTimer::timeout,this,&StationMeteo::OnTimeOutTimerMajBdd);
    timerMajBdd.start(15*60*1000);
    horodatage = QDateTime::currentDateTime();
}

void StationMeteo::TraiterTrameMeteo()
{
    QByteArray sortieStandard = processus->readAllStandardOutput();

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
        TrameStationWS3080 laTrame(trameCourante);
        horodatagePrec = horodatage;
        horodatage = laTrame.getHorodatage();
        idStation = laTrame.getIdStation();
        batterie = laTrame.getBatterie();

        if(horodatage > horodatagePrec.addSecs(20)) // pour éviter 2 trames successives on attend au moins 20s
        {
            temperatureHumidite = TemperatureHumidite(laTrame.getTemperature(),laTrame.getHumidite());
            pluie = laTrame.getPluie();
            cumulTemperatureHumidite += temperatureHumidite;
            qDebug() << QDateTime::currentDateTime();
            qDebug() << laTrame.getTemperature() << " -- " << laTrame.getHumidite();
            // WebsSocket
            QString id = QString::number(idStation);
            if (id== "169")
                id = "53";
            QString tem = QString::number(laTrame.getTemperature(),'f',1);
            QString hum = QString::number(laTrame.getHumidite());
            QString plu = QString::number(laTrame.getPluie());
            QString dir = QString::number(laTrame.getDirectionDuVent());
            QString vit = QString::number(laTrame.getVitesseDuVent(),'f',1);
            QString raf = QString::number(laTrame.getVitesseRafale(),'f',1);

            QString json = QString("{\"Station\":%1,\"Temperature\":%2,").arg(id,tem);
            json += QString("\"Humidite\":%1,\"Pluie\":%2,\"Direction\":%3,").arg(hum,plu,dir);
            json += QString("\"Vitesse\":%1,\"Rafale\":%2}").arg(vit,raf);
            leServeur.processTextMessage(json);
        }
        else
        {
            qDebug() << "inférieur";
        }
        trameCourante.clear();
    }
}



QString StationMeteo::getBatterie() const
{
    return batterie;
}

void StationMeteo::OnTimeOutTimerMajBdd()
{
    laBdd.EnregistrerTemperatureHumidite(idStation,
                                         cumulTemperatureHumidite.ObtenirValeurMoyenne(),
                                         QDateTime::currentDateTime()
                                         );
}

QDateTime StationMeteo::getHorodatage() const
{
    return horodatage;
}

int StationMeteo::getIdStation() const
{
    return idStation;
}
