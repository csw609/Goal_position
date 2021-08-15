#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

#include<iostream>
#include<fstream>
#include<qdebug.h>
#include<string.h>
#include<string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(add);
    ui->label_pic->setPixmap(pix);
}

MainWindow::MainWindow(std::string q, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_pic->installEventFilter(this);
    add = QString::fromStdString(q);
    QPixmap pix(add);

    int w = pix.size().width();
    int h = pix.size().height();
    wid = w;
    hei = h;
    //ui->label_pic->geometry().size().setWidth(w*2);
    //ui->label_pic->geometry().size().setHeight(h*2);
    ui->ns1->setGeometry(0,hei*2,60,25);
    ui->ns2->setGeometry(60,hei*2,60,25);
    ui->label_pic->setGeometry(0,0,w*2,h*2);
    ui->label_pic->setPixmap(pix.scaled(w * 2,h * 2));

    //parent->size().setHeight(1000);
}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->label_pic && event->type() == QMouseEvent::MouseButtonPress)
    {
        qDebug("label Clicked !!");
        std::fstream f;
        std::fstream m;

        QString adr = add;
        adr.chop(4);
        adr += ".yaml";
        qDebug() << adr;

        std::string ad = adr.toStdString();
        m.open(ad);
        std::string origin;
        getline(m,origin);
        getline(m,origin);
        getline(m,origin);
        QString org = QString::fromStdString(origin);
        org.remove(0,9);
        org.chop(1);
        QStringList list = org.split(",");

        qDebug() << list[0];
        qDebug() << list[1];

        QPoint pos = QWidget::mapToGlobal(ui->label_pic->rect().topLeft());
        QPoint pos2 = QCursor::pos();

        double x = pos2.x() - pos.x();
        double y = pos2.y() - pos.y();
        double cx = list[0].toDouble();
        double cy = list[1].toDouble();
        double ratioX = (double)wid / 20.0;
        double ratioY = (double)hei / 20.0;

        double mapX = x /(wid * 2) * ratioX;
        double mapY = (hei * 2 - y) / (hei * 2) * ratioY;

        mapX += cx;
        mapY += cy;

        qDebug() << mapX << " " << mapY;
        qDebug() << ratioX << " " << ratioY;

        f.open("/home/csw/catkin_ws/src/MultiRobot/src/"+ group.toStdString());
        f << mapX << "\n" << mapY;
        m.close();
        f.close();
    }
    return QWidget::eventFilter(target, event);
}

void MainWindow::on_ns1_clicked()
{
    group = "ns1";
}

void MainWindow::on_ns2_clicked()
{
    group = "ns2";
}
