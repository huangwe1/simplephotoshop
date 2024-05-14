#ifndef SECOND_H
#define SECOND_H

#include <QMainWindow>
#include "mainwindow.h"
namespace Ui {
class second;
}

class second : public QMainWindow
{
    Q_OBJECT

public:
    explicit second(QWidget *parent = 0);
        ~second();
    MainWindow *window = NULL;
private slots:
    void on_pushButton_clicked();


private:
    Ui::second *ui;
};

#endif // SECOND_H
