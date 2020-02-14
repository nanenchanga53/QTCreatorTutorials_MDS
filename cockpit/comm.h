#ifndef COMM_H
#define COMM_H

#include <QObject>

class QTcpSocket;

class comm : public QObject
{
    Q_OBJECT

public:
    comm();

    QTcpSocket* sck_lidar;
    QTcpSocket* sck_cam;
    QTcpSocket* sck_sonar;
    QTcpSocket* sck_imu;

signals:
    void send_YPR(float, float, float);

public slots:
    void connect_cam(QString, QString);
    void connect_lidar(QString, QString);
    void connect_sonar(QString, QString);
    void connect_imu(QString, QString);
    void disconnect_system();


    void readLidar();
    void disLidar();
    void conLidar();

    void readCam();
    void disCam();
    void conCam();

    void readImu();
    void disImu();
    void conImu();

    void readSonar();
    void disSonar();
    void conSonar();
};

#endif // COMM_H
