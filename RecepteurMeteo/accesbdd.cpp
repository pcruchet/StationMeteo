#include "accesbdd.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
#include <QFileInfo>

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

    QFileInfo testFichier("config.ini");
    QString serveur ;
    QString utilisateur ;
    QString motDePasse ;
    QString base ;
    if(testFichier.exists() && testFichier.isFile())
    {
        qDebug() << "FichierIni Ok";
        QSettings initialisation("config.ini",QSettings::IniFormat);
        serveur = initialisation.value("BaseDeDonnees/serveur","127.0.0.1").toString();
        utilisateur = initialisation.value("BaseDeDonnees/utilisateur","philippe").toString();
        motDePasse = initialisation.value("BaseDeDonnees/motDePasse","123").toString();
        base = initialisation.value("BaseDeDonnees/base","Meteo").toString();
    }
    else
    {
        qDebug() << "Erreur lecture fichier ini";
    }

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
bool AccesBDD::EnregistrerTemperatureHumidite(const int _idStation, const double _temperature, const int _humidite)
{
    bool retour = false;
    if(bddMeteo.isOpen())
    {
        while(!bddMeteo.transaction());
        QDateTime horodatageActuelle = QDateTime::currentDateTime();
        QSqlQuery requette(bddMeteo.database());

        // récupération des deux dernières valeurs enregistrées
        requette.prepare("SELECT * FROM TemperatureHumidite WHERE idStation = :id ORDER BY horodatage DESC LIMIT 0,2 ");
        requette.bindValue(":id",_idStation);
        bool repetition = false;
        if(!requette.exec())
        {
            qDebug() << "Problème dans la requette EnregistrerTemperatureHumidite 1" ;
            qDebug() << getLastExecutedQuery(requette);
            qDebug() << bddMeteo.lastError();
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
                    qDebug() << getLastExecutedQuery(requette);
                    qDebug() << bddMeteo.lastError();
                    bddMeteo.rollback();
                }
                else
                {
                    qDebug() << getLastExecutedQuery(requette);
                    bddMeteo.commit();
                    retour = true;
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
                bddMeteo.rollback();
            }
            else
            {
                qDebug() << getLastExecutedQuery(requette);
                bddMeteo.commit();
                retour = true;
            }
        }
    }
    else
    {
        qDebug() << "La base de données n'est pas ouverte ";
    }
    return retour;
}
/**
 * @brief AccesBDD::EnregistrerVent
 * @param _idStation    Identifiant de la station
 * @param _vitesse      Valeur de la vitesse du vent en m/s
 * @param _direction    Valeur de la direction du vent en degré
 * @param _rafale       Valeur de la plus grosse rafale en m/s
 *
 * @details Enregistre la vitesse du vent et sa direction ainsi que la vitesse de
 *          la plus grosse rafal sur la période.
 *
 */
void AccesBDD::EnregistrerVent(const int _idStation, const double _vitesse, const int _direction, const double _rafale)
{
    if(bddMeteo.isOpen())
    {
        QSqlQuery requette(bddMeteo.database());
        requette.prepare("INSERT INTO `Vent` (`horodatage`, `vitesse`, `direction`, `rafale`,`idStation`) "
                         "VALUES (now(), :vVent, :dVent, :rVent, :station);");
        requette.bindValue(":vVent",_vitesse);
        requette.bindValue(":dVent",_direction);
        requette.bindValue(":rVent",_rafale);
        requette.bindValue(":station",_idStation);
        if(!requette.exec())
        {
            qDebug() << requette.lastQuery();
            qDebug() << "Problème dans la requette EnregistrerVent" ;
            qDebug() << getLastExecutedQuery(requette);
            qDebug() << bddMeteo.lastError();
        }
        else
        {
            qDebug() << getLastExecutedQuery(requette);
        }
    }

}

bool AccesBDD::EnregistrerPluie(const int _idStation, const double _pluie)
{
    bool retour = false;
    if(bddMeteo.isOpen())
    {
        while(!bddMeteo.transaction());
        bool repetition = false;
        QDateTime horodatageActuelle = QDateTime::currentDateTime();
        QSqlQuery requette(bddMeteo.database());
        if(_pluie < 0.1)
        {


            // récupération des deux dernières valeurs enregistrées
            requette.prepare("SELECT * FROM Pluie WHERE idStation = :id ORDER BY horodatage DESC LIMIT 0,2 ");
            requette.bindValue(":id",_idStation);

            if(!requette.exec())
            {
                bddMeteo.rollback();
                qDebug() << "Problème dans la requette EnregistrerPluie 1" ;
                qDebug() << getLastExecutedQuery(requette);
                qDebug() << bddMeteo.lastError();
            }
            int nbLignes = requette.size();
            if(nbLignes == 2)
            {

                QDateTime horodatage ;

                double valeurs[2];
                if(requette.first())
                {
                    horodatage = requette.value("horodatage").toDateTime();
                    valeurs[0] = requette.value("quantite").toDouble();
                }
                if(requette.last())
                {
                    valeurs[1] = requette.value("quantite").toDouble();
                }

                // si la nouvelle valeur est identique au deux dernières valeurs enregistrées
                if(valeurs[0] == _pluie && valeurs[0] == valeurs[1])
                {
                    requette.prepare("UPDATE Pluie SET horodatage = :nouvelle WHERE horodatage = :ancienne AND idStation = :id");
                    requette.bindValue(":nouvelle", horodatageActuelle);
                    requette.bindValue(":ancienne",horodatage);
                    requette.bindValue(":id",_idStation);

                    repetition = true;
                    if(!requette.exec())
                    {
                        qDebug() << "Problème dans la requette EnregistrerPluie 2" ;
                        qDebug() << getLastExecutedQuery(requette);
                        qDebug() << bddMeteo.lastError();
                        bddMeteo.rollback();
                    }
                    else
                    {
                        qDebug() << getLastExecutedQuery(requette);
                        bddMeteo.commit();
                        retour = true;
                    }
                }
            }
        }
        // insertion normale dans la BDD si il n'y a pas de répétition
        if(!repetition)
        {

            requette.prepare("INSERT INTO `Pluie` (`horodatage`, `quantite`, `idStation`) "
                             "VALUES (now(), :qte, :station);");
            requette.bindValue(":qte",_pluie);
            requette.bindValue(":station",_idStation);
            if(!requette.exec())
            {
                qDebug() << requette.lastQuery();
                qDebug() << horodatageActuelle << " - " << _pluie ;
                qDebug() << "Problème dans la requette EnregistrerPluie 3" ;
                qDebug() << getLastExecutedQuery(requette);
                qDebug() << bddMeteo.lastError();
                bddMeteo.rollback();
            }
            else
            {
                qDebug() << getLastExecutedQuery(requette);
                bddMeteo.commit();
                retour = true;
            }
        }
    }
    else
    {
        qDebug() << "La base de données n'est pas ouverte ";
    }
    return retour;
}

bool AccesBDD::ActualiserEtatBatterie(const int _idStation, const bool _etat)
{
    bool retour = false;
    if(bddMeteo.isOpen())
    {
        while(!bddMeteo.transaction());

        QSqlQuery requette(bddMeteo.database());

        requette.prepare("SELECT * FROM Batterie WHERE idStation = :id ORDER BY horodatage DESC LIMIT 0,1 ");
        requette.bindValue(":id",_idStation);

        if(!requette.exec())
        {
            qDebug() << "Problème dans la requette ActualiserEtatBatterie 1" ;
            qDebug() << getLastExecutedQuery(requette);
            qDebug() << bddMeteo.lastError();
        }

        if((requette.first() && _etat != requette.value("etat").toBool()) || requette.size() == 0)
        {
            requette.prepare("INSERT INTO `Batterie` (`horodatage`,`idStation`, 'etat') "
                             "VALUES (now(),:station), :batterie;");
            requette.bindValue(":station",_idStation);
            requette.bindValue(":batterie",_etat);
            if(!requette.exec())
            {
                qDebug() << "Problème dans la requette ActualiserEtatBatterie 2" ;
                qDebug() << getLastExecutedQuery(requette);
                qDebug() << bddMeteo.lastError();
                bddMeteo.rollback();
            }
            else
            {
                qDebug() << getLastExecutedQuery(requette);
                bddMeteo.commit();
                retour = true;
            }
        }
    }
    return retour;
}
