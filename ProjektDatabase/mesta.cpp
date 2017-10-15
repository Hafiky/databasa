#include "mesta.h"
#include "ui_mesta.h"

Mesta::Mesta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mesta)
{
    ui->setupUi(this);
}

QString Mesta::getJmeno()
{
    return ui->lineEdit->text();
}

QSpinBox* Mesta::getPSC()
{
    return ui->spinBox;
}

Mesta::~Mesta()
{
    delete ui;
}
