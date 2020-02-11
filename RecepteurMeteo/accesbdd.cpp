#include "accesbdd.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

AccesBDD::AccesBDD(QObject *parent) : QObject(parent)
{
    bddMeteo =  QSqlDatabase::addDatabase(("QMYSQL"));
    bddMeteo.setHostName("127.0.0.1");  //@RPI
    bddMeteo.setUserName("root");       //philippe
    bddMeteo.setPassword("toto");       //123
    bddMeteo.setDatabaseName("meteo");  //Meteo

    if(bddMeteo.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << bddMeteo.hostName() ;

    }
    else
    {
        qDebug() << "La connexion a échouée, désolé" << bddMeteo.lastError();
    }
}

AccesBDD::~AccesBDD()
{
    bddMeteo.close();
}


void AccesBDD::EnregistrerTemperatureHumidite(const int _idStation, const double _temperature, const int _humidite)
{
    if(bddMeteo.isOpen())
    {
        QDateTime horodatageActuelle = QDateTime::currentDateTime();
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
            if(valeurs[0] == TemperatureHumidite(_temperature,_humidite) && valeurs[0] == valeurs[1])
            {
                requette.prepare("UPDATE TemperatureHumidite SET horodatage = :nouvelle WHERE horodatage = :ancienne AND idStation = :id");
                requette.bindValue(":nouvelle", horodatageActuelle);
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
            requette.bindValue(":horodatage",horodatageActuelle);
            requette.bindValue(":temp",_temperature);
            requette.bindValue(":hum",_humidite);
            requette.bindValue(":station",_idStation);
            if(!requette.exec())
            {
                qDebug() << requette.lastQuery();
                qDebug() << horodatageActuelle << " - " << _temperature << " - " << _humidite;
                qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 3" ;
            }
        }
    }
    else
    {
        qDebug() << "La base de données n'est pas ouverte ";
    }
}
