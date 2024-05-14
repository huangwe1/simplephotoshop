#include "third.h"
#include "ui_third.h"

third::third(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::third)
{
    ui->setupUi(this);
    this->window = new second;
    QPixmap pixmap=QPixmap(":/icon/adobe-photoshop-logo_00(1).png").scaled(this->size());
    QPalette palette;
    //设置主窗口背景图片
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
}

third::~third()
{
    delete ui;
}
void third::mousePressEvent(QMouseEvent *event)
{
    this->hide();
    window->show();
}
