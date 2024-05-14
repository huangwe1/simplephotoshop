#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include "photoset.h"
namespace Ui {
class SizeDialog;
}

class SizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeDialog(QWidget *parent = 0);
    ~SizeDialog();
    void setWidget(photoset *y);
    bool savesetting;
public slots:
    void saveSetting();

private:
    Ui::SizeDialog *ui;
    photoset *s;
    double width;
    double height;

};

#endif // SIZEDIALOG_H
