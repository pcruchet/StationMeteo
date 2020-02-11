#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "accesbdd.h"
#include "stationmeteo.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLancer_clicked();
    void MettreAJour();

private:
    Ui::MainWindow *ui;
    QProcess *processus;
    QString  chaine;

    AccesBDD laBdd;
    StationMeteo *laStation;
};

#endif // MAINWINDOW_H
