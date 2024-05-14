#include "second.h"
#include "ui_second.h"
#include <QMessageBox>
second::second(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::second)
{
    this->setWindowTitle("登陆界面");
    ui->setupUi(this);
    this->window = new MainWindow;
    QPixmap pixmap=QPixmap(":/icon/6284-1104121A52151.jpg").scaled(this->size());
    QPalette palette;
    //设置主窗口背景图片
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
    ui->word->setEchoMode(QLineEdit::Password);
}

second::~second()
{
    delete ui;
}

void second::on_pushButton_clicked()
{
    if(ui->Number->text() == "2312068" && ui->word->text() == "12345678"){
        this->close();
        window->show();
    }else{
        QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
        ui->Number->clear();
        ui->word->clear();
        ui->Number->setFocus();
    }
}
