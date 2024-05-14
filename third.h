#ifndef THIRD_H
#define THIRD_H

#include <QMainWindow>
#include "second.h"
namespace Ui {
class third;
}

class third : public QMainWindow
{
    Q_OBJECT

public:
    explicit third(QWidget *parent = 0);
    ~third();

    second *window = NULL;
private slots:

private:
    Ui::third *ui;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // THIRD_H
