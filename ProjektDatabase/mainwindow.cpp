#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlTableModel>
#include "internet.h"
#include <QSqlQuery>
#include <QItemSelectionModel>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QInputDialog>
#include "mesta.h"
#include "konekt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../pes/ProjektDatabase/projekt.db");
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("mesta");
    model->setHeaderData(1, Qt::Horizontal, "Název města");
    model->setHeaderData(2, Qt::Horizontal, "PSC");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->hideColumn(0);
    model_2 = new QSqlTableModel(this);
    model_2->setTable("internet");
    model_2->setHeaderData(1, Qt::Horizontal, "Název internetů");
    model_2->setHeaderData(2, Qt::Horizontal, "Vedoucí");
    model_2->select();
    ui->tableView_2->setModel(model_2);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->hideColumn(0);



    model_3 = new QSqlQueryModel(this);

    ui->tableView_3->setModel(model_3);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    model_3->setQuery("SELECT konekt.id,mesta.jmeno,internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id ");
    ui->tableView_3->hideColumn(0);
    model_3->setHeaderData(0, Qt::Horizontal, tr("Jména měst"));
    model_3->setHeaderData(0, Qt::Horizontal, tr("Jména Internetů"));
   // model_4->setHeaderData(0, Qt::Horizontal, tr("Jména měst"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mesto_add_clicked()
{
    Mesta m;
    if(m.exec() == QDialog::Accepted)
    {
        //qDebug()<< m.getPSC()->value();
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO mesta VALUES(NULL, :jmeno, :psc)");
        dotaz.bindValue(":jmeno", m.getJmeno());
        dotaz.bindValue(":psc", m.getPSC()->value());
        dotaz.exec();
        model->select();

    }
}

void MainWindow::on_mesto_remove_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QString sql = "DELETE FROM mesta WHERE id IN (";
    QString sql2 = "DELETE FROM konekt WHERE id_mesta IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        sql+= QString::number(model->data(index).toInt());
        sql2+= QString::number(model->data(index).toInt());
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
            sql2+=", ";
        }
    }
    qDebug()<<sql;
    qDebug()<<sql2;
    sql+=")";
    sql2+=")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    QSqlQuery dotaz2;
    dotaz2.prepare(sql2);
    dotaz2.exec();
    model->select();
    model_3->setQuery("SELECT konekt.id,mesta.jmeno,internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id ");


}

void MainWindow::on_mesto_move_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (selection->selectedRows().count()>1) {
        QMessageBox::warning(this,"Ty Zmrde!","Musíš selectit jen 1 řádok že?");
    }else{
        QModelIndex index = selection->selectedRows().at(0);
        int id= (model->data(index).toInt());


      ui->tabWidget->setCurrentIndex(3);
      model_4 = new QSqlQueryModel;
      model_4->setQuery("SELECT internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id and mesta.id="+QString::number(id));
      ui->tableView_4->setModel(model_4);
      model_4->setHeaderData(0, Qt::Horizontal, tr("Jména internetů"));

//      ui->comboBox->clear();
//      mesto=true;

//      QSqlQuery dotaz;
//      dotaz.prepare("SELECT * FROM internet");
//      dotaz.exec();
//      while(dotaz.next())
//      {
//          ui->comboBox->insertItem(0,dotaz.value("jmeno").toString(), dotaz.value("id"));
//      }



}}

void MainWindow::on_internet_add_clicked()
{
    Internet i;
    if(i.exec() == QDialog::Accepted)
    {
        //qDebug()<< m.getPSC()->value();
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO internet VALUES(NULL, :jmeno, :psc)");
        dotaz.bindValue(":jmeno", i.getJmeno());
        dotaz.bindValue(":psc", i.getVedouci());
        dotaz.exec();
        model_2->select();

    }
}

void MainWindow::on_internet_remove_clicked()
{
    QItemSelectionModel *selection = ui->tableView_2->selectionModel();
    QString sql = "DELETE FROM internet WHERE id IN (";
    QString sql2 = "DELETE FROM konekt WHERE id_internet IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        sql+= QString::number(model_2->data(index).toInt());
        sql2+= QString::number(model_2->data(index).toInt());
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
            sql2+=", ";
        }
    }
    sql+=")";
    sql2+=")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    QSqlQuery dotaz2;
    dotaz2.prepare(sql2);
    dotaz2.exec();
    model_2->select();
    model_3->setQuery("SELECT konekt.id,mesta.jmeno,internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id ");

}

void MainWindow::on_internet_move_clicked()
{
    QItemSelectionModel *selection = ui->tableView_2->selectionModel();
    if (selection->selectedRows().count()>1) {
        QMessageBox::warning(this,"Ty Zmrde!","Musíš selectit jen 1 řádok že?");
    }else{
        QModelIndex index = selection->selectedRows().at(0);
        int id= (model_2->data(index).toInt());


      ui->tabWidget->setCurrentIndex(3);
      model_4 = new QSqlQueryModel;
      model_4->setQuery("SELECT mesta.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id and internet.id="+QString::number(id));
      ui->tableView_4->setModel(model_4);
      model_4->setHeaderData(0, Qt::Horizontal, tr("Jména měst"));

//      ui->comboBox->clear();
//      mesto=false;

//      QSqlQuery dotaz;
//      dotaz.prepare("SELECT * FROM mesta");
//      dotaz.exec();
//      while(dotaz.next())
//      {
//          ui->comboBox->insertItem(0,dotaz.value("jmeno").toString(), dotaz.value("id"));
//      }

}}

void MainWindow::on_mesto_add_internet_clicked()
{
    if (mesto) {

    }else{

    }
}

void MainWindow::on_pushButton_clicked()
{
    Konekt k;
    if(k.exec() == QDialog::Accepted)
    {
        QSqlQuery dotaz;
        dotaz.prepare("SELECT id FROM konekt WHERE konekt.id_mesta=:idmesto and konekt.id_internet=:idinternet");
        dotaz.bindValue(":idmesto", k.getMestoId());
        dotaz.bindValue(":idinternet", k.getInternetId());
        qDebug()<<"stejny"<<k.getMestoId()<<k.getInternetId();
        dotaz.exec();

        if (dotaz.next()) {
           qDebug()<<"stejny";
           QMessageBox::warning(this,"BACHA!","Tato databaze je tak vymakaná, že nemůžeš vložit duplikátní hodnoty");

        }else{
            qDebug()<<"neni stejny";
            dotaz.prepare("INSERT INTO konekt VALUES(NULL, :jmeno, :psc)");
            dotaz.bindValue(":jmeno", k.getMestoId());
            dotaz.bindValue(":psc", k.getInternetId());
            dotaz.exec();
            model_3->setQuery("SELECT konekt.id,mesta.jmeno,internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id ");

        }
        //qDebug()<< k.getMestoId();
        //QSqlQuery dotaz;

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QItemSelectionModel *selection = ui->tableView_3->selectionModel();
    QString sql = "DELETE FROM konekt WHERE id IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        qDebug()<<index;
        sql+= QString::number(model_3->data(index).toInt());
        qDebug()<<model_3->data(index);
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
        }
    }
    sql+=")";
    qDebug()<<sql;
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    model_3->setQuery("SELECT konekt.id,mesta.jmeno,internet.jmeno FROM internet ,konekt , mesta where mesta.id=konekt.id_mesta and konekt.id_internet = internet.id ");
}
