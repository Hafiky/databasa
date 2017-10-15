#ifndef MESTA_H
#define MESTA_H

#include <QDialog>
#include <QSpinBox>


namespace Ui {
class Mesta;
}

class Mesta : public QDialog
{
    Q_OBJECT

public:
    explicit Mesta(QWidget *parent = 0);
    QString getJmeno();
    QSpinBox *getPSC();
    ~Mesta();

private:
    Ui::Mesta *ui;
};

#endif // MESTA_H
