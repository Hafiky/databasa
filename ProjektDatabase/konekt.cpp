#include "konekt.h"
#include "ui_konekt.h"

Konekt::Konekt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Konekt)
{
    ui->setupUi(this);
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("../../pes/ProjektDatabase/projekt.db");
//    db.open();
    QSqlQuery dotaz;
    dotaz.prepare("SELECT * FROM mesta");
    dotaz.exec();
    while(dotaz.next())
    {
        ui->comboBox->insertItem(0,dotaz.value("jmeno").toString(), dotaz.value("id"));
    }
    dotaz.prepare("SELECT * FROM internet");
    dotaz.exec();
    while(dotaz.next())
    {
        ui->comboBox_2->insertItem(0,dotaz.value("jmeno").toString(), dotaz.value("id"));
    }
}

int Konekt::getMestoId()
{
    return ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
}

int Konekt::getInternetId()
{
    return ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toInt();
}

Konekt::~Konekt()
{
    delete ui;
}
