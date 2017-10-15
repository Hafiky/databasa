#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mesto_add_clicked();

    void on_mesto_remove_clicked();

    void on_mesto_move_clicked();

    void on_internet_add_clicked();

    void on_internet_remove_clicked();

    void on_internet_move_clicked();

    void on_mesto_add_internet_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlTableModel *model_2;
    QSqlQueryModel *model_3;
    QSqlQueryModel *model_4;
    QSqlDatabase db;
    bool mesto;
};

#endif // MAINWINDOW_H
