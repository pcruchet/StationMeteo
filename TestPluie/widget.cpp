#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    laPluie(10)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Ajouter_clicked()
{
    laPluie.Ajouter(ui->lineEdit_Cumul->text().toDouble());
}

void Widget::on_pushButton_Visualiser_clicked()
{
    double valeur = laPluie.ObtenirCumul();
    ui->lineEdit_Resultat->setText(QString::number(valeur,'g','3'));
}

void Widget::on_pushButton_Purger_clicked()
{
    laPluie.Purger();
}
