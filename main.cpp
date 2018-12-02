#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
   // w.setFixedSize(730,580);
    w.show();

    return a.exec();
}
