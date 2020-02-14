#include "common.h"
#include "cockpit.h"
#include "ivi.h"
#include "cont.h"
#include "comm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cockpit w;
    w.move(0, 0);
    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    ivi w2;
    w2.move(w.pos().rx() + w.width() + 166, 0);
    //w2.setWindowFlags(Qt::FramelessWindowHint);
    w2.show();
    cont w3;
    w3.move(0, w.pos().ry() + w.height() + 225);
    //w3.setWindowFlags(Qt::FramelessWindowHint);
    w3.show();

    comm cls_comm;

    QObject::connect(&cls_comm, SIGNAL(send_YPR(float, float, float)), &w, SLOT(recv_YPR(float, float, float)));
    QObject::connect(&w2, SIGNAL(startSystem()), &w3, SLOT(connectDevice()));
    QObject::connect(&w2, SIGNAL(endSystem()), &w3, SLOT(disconnectDevice()));

    QObject::connect(&w3, SIGNAL(connLidar(QString, QString)), &cls_comm, SLOT(connect_lidar(QString, QString)));
    QObject::connect(&w3, SIGNAL(connCam(QString, QString)), &cls_comm, SLOT(connect_cam(QString, QString)));
    QObject::connect(&w3, SIGNAL(connImu(QString, QString)), &cls_comm, SLOT(connect_imu(QString, QString)));
    QObject::connect(&w3, SIGNAL(connSonar(QString, QString)), &cls_comm, SLOT(connect_sonar(QString, QString)));

    QObject::connect(&w3, SIGNAL(disconn()), &cls_comm, SLOT(disconnect_system()));

    return a.exec();
}


//    ultra w;
//    w.move(0,0);
//    //w.setWindowFlags(Qt::FramelessWindowHint);
//    w.show();
//    imu w2;
//    w2.move(530,0);
//    //w2.setWindowFlags(Qt::FramelessWindowHint);
//    w2.show();
//    lidar w3;
//    w3.move(930,0);
//    //w3.setWindowFlags(Qt::FramelessWindowHint);
//    w3.show();
//    lidar_adv w4;
//    w4.move(0,500);
//    //w4.setWindowFlags(Qt::FramelessWindowHint);
//    w4.show();
//    camera w5;
//    w5.move(530,500);
//    //w5.setWindowFlags(Qt::FramelessWindowHint);
//    w5.show();
//    camera_adv w6(nullptr, &w4);
//    w6.move(930,500);
//    //w5.setWindowFlags(Qt::FramelessWindowHint);
//    w6.show();

//    ///imu + lidar 연동 추가
//    QObject::connect(&w2, SIGNAL(imusend(int)), &w4, SLOT(imuRecv(int)));
