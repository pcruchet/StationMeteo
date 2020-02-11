#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "tramestationws3080.h"
#include "station.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    processus = new QProcess(this);
    laStation = new StationMeteo(processus,laBdd,this);
    connect(processus, &QProcess::readyReadStandardOutput,laStation,&StationMeteo::TraiterTrameMeteo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLancer_clicked()
{   QStringList arguments;
    arguments << "-R" << "32" << "-F" << "json"; //<< "-R" << "12"
    if(!processus->isTransactionStarted())
        processus->start("/home/pi/Meteo/build-rtl_433-Desktop-Défaut/src/rtl_433",arguments);
}

void MainWindow::MettreAJour()
{
    QByteArray tableau = processus->readAllStandardOutput();

    int indice = 0;
    while(tableau[indice] != '}' && indice < tableau.count())
    {

        chaine += tableau[indice++];
    }
    if(tableau[indice] == '}')
    {
        chaine += "}";
        if(chaine.at(0)== '"')
            chaine.remove(0,1);
        EchantillonMeteo laTrame(chaine);
        ui->lcdNumberTemperature->display(laTrame.getTemperature());
        ui->lcdNumberHumidite->display(laTrame.getHumidite());
        ui->dateTimeEditHorodatage->setDateTime(laTrame.getHorodatage());
        chaine.clear();
        laBdd.EnregistrerTemperatureHumidite(laTrame.getIdStation(),laTrame.getTemperatureHumidite(),laTrame.getHorodatage());
    }


}
