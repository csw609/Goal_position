#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("/home/csw/catkin_ws/src/map/lab_test.pgm");
    qDebug("Start");
    w.setFixedSize(w.wid *2,w.hei*2+50);
    w.show();

    return a.exec();
}
