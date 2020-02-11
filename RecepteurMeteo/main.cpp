#include <QCoreApplication>
#include "recepteurrtl_433.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RecepteurRTL_433 recepteur;
    recepteur.LancerEcoute();

    return a.exec();
}
