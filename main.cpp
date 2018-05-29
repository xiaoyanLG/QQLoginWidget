#include "xyqqloginwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XYQQLogInWidget w;
    w.resize(500, 350);
    w.show();

    return a.exec();
}
