#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "pluie.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Visualiser_clicked();

    void on_pushButton_Purger_clicked();

private:
    Ui::Widget *ui;
    Pluie laPluie;
};

#endif // WIDGET_H
