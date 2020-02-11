#include "accesbdd.h"
#include <QDebug>
#include <QSqlQuery>

AccesBDD::AccesBDD(QObject *parent) : QObject(parent)
{
    bddMeteo =  QSqlDatabase::addDatabase(("QMYSQL"));
    bddMeteo.setHostName("127.0.0.1");
    bddMeteo.setUserName("philippe");
    bddMeteo.setPassword("123");
    bddMeteo.setDatabaseName("Meteo");

    if(bddMeteo.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << bddMeteo.hostName() ;

    }
    else
    {
        qDebug() << "La connexion a échouée, désolé" ;
    }
}

AccesBDD::~AccesBDD()
{
    bddMeteo.close();
}

void AccesBDD::EnregistrerMeteo(TrameStationWS3080 _laTrame)
{
    QSqlQuery requete;
    requete.prepare("insert into Meteo.MesuresExterieures (horodatage, idStation,batterie,temperature,humidite,vitesseVent,directionVent, rafale, pluie"
                    "values (:horodatage, :station, :batterie, :temperature, :humidite, :vitesse, :direction, :rafale, :pluie");

    requete.bindValue(":horodatage",_laTrame.getHorodatage());
    requete.bindValue(":station", _laTrame.getIdStation());
    requete.bindValue(":batterie",_laTrame.getBatterie());
    requete.bindValue(":temperature",_laTrame.getTemperature());
    requete.bindValue(":humidite",_laTrame.getHumidite());
    requete.bindValue(":vitesse",_laTrame.getVitesseDuVent());
    requete.bindValue(":direction",_laTrame.getDirectionDuVent());
    requete.bindValue(":rafale",_laTrame.getVitesseRafale());
    requete.bindValue(":pluie",_laTrame.getPluie());
}

void AccesBDD::EnregistrerTemperatureHumidite(int _idStation, TemperatureHumidite _tempHum, QDateTime _horodatage)
{
    if(bddMeteo.isOpen())
    {
        QSqlQuery requette(bddMeteo.database());
        requette.prepare("SELECT * FROM TemperatureHumidite WHERE idStation = :id ORDER BY horodatage DESC LIMIT 0,2 ");
        requette.bindValue(":id",_idStation);
        bool repetition = false;

        if(!requette.exec())
        {
            qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 1" ;
        }
        int nbLignes = requette.size();
        if(nbLignes == 2)
        {
            double temperature;
            int humidite;
            QDateTime horodatage ;
            TemperatureHumidite valeurs[2];
            if(requette.first())
            {
                horodatage = requette.value("horodatage").toDateTime();
                temperature = requette.value("temperature").toDouble();
                humidite = requette.value("humidite").toInt();
                valeurs[0] = TemperatureHumidite(temperature,humidite);
            }
            if(requette.last())
            {
                temperature = requette.value("temperature").toDouble();
                humidite = requette.value("humidite").toInt();
                valeurs[1] = TemperatureHumidite(temperature,humidite);
            }
            if(valeurs[0] == _tempHum && valeurs[0] == valeurs[1])
            {
                requette.prepare("UPDATE TemperatureHumidite SET horodatage = :nouvelle WHERE horodatage = :ancienne AND idStation = :id");
                requette.bindValue(":nouvelle", _horodatage);
                requette.bindValue(":ancienne",horodatage);
                requette.bindValue(":id",_idStation);

                repetition = true;
                if(!requette.exec())
                {
                    qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 2" ;
                }
            }
        }

        if(!repetition)
        {
            requette.prepare("INSERT INTO `TemperatureHumidite` (`horodatage`, `temperature`, `humidite`, `idStation`) "
                             "VALUES (:horodatage, :temp, :hum, :station);");
            requette.bindValue(":horodatage",_horodatage);
            requette.bindValue(":temp",_tempHum.getTemperature());
            requette.bindValue(":hum",_tempHum.getHumidite());
            requette.bindValue(":station",_idStation);
            if(!requette.exec())
            {
                qDebug() << requette.lastQuery();
                qDebug() << _horodatage << " - " << _tempHum.getTemperature() << " - " << _tempHum.getHumidite();
                qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 3" ;
            }
        }
    }
    else
    {
        qDebug() << "La base de données n'est pas ouverte ";
    }
}
