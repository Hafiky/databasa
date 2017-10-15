#ifndef KONEKT_H
#define KONEKT_H

#include <QDialog>
#include <QComboBox>
#include <QtSql/QSqlTableModel>
#include <QSqlQuery>
#include <QItemSelectionModel>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class Konekt;
}

class Konekt : public QDialog
{
    Q_OBJECT

public:
    explicit Konekt(QWidget *parent = 0);
    int getMestoId();
    int getInternetId();
    ~Konekt();

private:
    Ui::Konekt *ui;
    QSqlDatabase db;
};

#endif // KONEKT_H
