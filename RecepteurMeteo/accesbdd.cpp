#include "accesbdd.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>

QString getLastExecutedQuery(const QSqlQuery& query)
{
 QString str = query.lastQuery();
 QMapIterator<QString, QVariant> it(query.boundValues());
 while (it.hasNext())
 {
  it.next();
  str.replace(it.key(),it.value().toString());
 }
 return str;
}

AccesBDD::AccesBDD(QObject *parent) : QObject(parent)
{
    QSettings initialisation("config.ini",QSettings::IniFormat);
    QString serveur = initialisation.value("BaseDeDonnees/serveur").toString();
    QString utilisateur = initialisation.value("BaseDeDonnees/utilisateur").toString();
    QString motDePasse = initialisation.value("BaseDeDonnees/motDePasse").toString();
    QString base = initialisation.value("BaseDeDonnees/base").toString();

    bddMeteo =  QSqlDatabase::addDatabase(("QMYSQL"));
    bddMeteo.setHostName(serveur);
    bddMeteo.setUserName(utilisateur);
    bddMeteo.setPassword(motDePasse);
    bddMeteo.setDatabaseName(base);

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

/**
 * @brief AccesBDD::EnregistrerTemperatureHumidite
 * @param _idStation    Identifiant de la station
 * @param _temperature  Valeur de la température
 * @param _humidite     Valeur de l'humidité
 *
 * @details Enregistre la température et l'humidité de l'air en évitant les doublons
 *          dans la base de données
 */
void AccesBDD::EnregistrerTemperatureHumidite(const int _idStation, const double _temperature, const int _humidite)
{
    if(bddMeteo.isOpen())
    {
        QDateTime horodatageActuelle = QDateTime::currentDateTime();
        QSqlQuery requette(bddMeteo.database());

        // récupération des deux dernières valeurs enregistrées
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

            // si la nouvelle valeur est identique au deux dernières valeurs enregistrées
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

        // insertion normale dans la BDD si il n'y a pas de répétition
        if(!repetition)
        {

            requette.prepare("INSERT INTO `TemperatureHumidite` (`horodatage`, `temperature`, `humidite`, `idStation`) "
                             "VALUES (now(), :temp, :hum, :station);");
            requette.bindValue(":temp",_temperature);
            requette.bindValue(":hum",_humidite);
            requette.bindValue(":station",_idStation);
            if(!requette.exec())
            {
                qDebug() << requette.lastQuery();
                qDebug() << horodatageActuelle << " - " << _temperature << " - " << _humidite;
                qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 3" ;
                qDebug() << getLastExecutedQuery(requette);
                qDebug() << bddMeteo.lastError();
            }
        }
    }
    else
    {
        qDebug() << "La base de données n'est pas ouverte ";
    }
}

void AccesBDD::EnregistrerVent(const int _idStation, const double _vitesse, const int _direction, const double _rafale)
{
    if(bddMeteo.isOpen())
    {
        QDateTime horodatageActuelle = QDateTime::currentDateTime();
        QSqlQuery requette(bddMeteo.database());
        requette.prepare("SELECT * FROM Vent WHERE idStation = :id ORDER BY horodatage DESC LIMIT 0,2 ");
        requette.bindValue(":id",_idStation);
        bool repetition = false;
        if(!requette.exec())
        {
            qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 1" ;
        }
        int nbLignes = requette.size();
        if(nbLignes == 2)
        {

        }
    }

}

void AccesBDD::ActualiserEtatBatterie(const int _idStation, const bool _etat)
{

}
