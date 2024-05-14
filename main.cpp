  #include "third.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    third w;
    w.show();

    return a.exec();
}
