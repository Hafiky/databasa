#ifndef INTERNET_H
#define INTERNET_H

#include <QDialog>

namespace Ui {
class Internet;
}

class Internet : public QDialog
{
    Q_OBJECT

public:
    explicit Internet(QWidget *parent = 0);
     QString getJmeno();
     QString getVedouci();
    ~Internet();

private:
    Ui::Internet *ui;
};

#endif // INTERNET_H
