#include "internet.h"
#include "ui_internet.h"

Internet::Internet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Internet)
{
    ui->setupUi(this);
}

QString Internet::getJmeno()
{
    return ui->lineEdit->text();
}

QString Internet::getVedouci()
{
    return ui->lineEdit_2->text();
}

Internet::~Internet()
{
    delete ui;
}
