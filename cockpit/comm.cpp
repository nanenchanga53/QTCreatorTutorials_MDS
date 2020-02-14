#include "comm.h"
#include "common.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

comm::comm() : QObject()
{
    // tcp 객체 생성
    sck_lidar = new QTcpSocket();
    sck_cam = new QTcpSocket();
    sck_imu = new QTcpSocket();
    sck_sonar = new QTcpSocket();

    connect(sck_lidar, SIGNAL(readyRead()), this, SLOT(readLidar()));
    connect(sck_lidar, SIGNAL(disconnected()), this, SLOT(disLidar()));
    connect(sck_lidar, SIGNAL(connected()), this, SLOT(conLidar()));

    connect(sck_cam, SIGNAL(readyRead()), this, SLOT(readCam()));
    connect(sck_cam, SIGNAL(disconnected()), this, SLOT(disCam()));
    connect(sck_cam, SIGNAL(connected()), this, SLOT(conCam()));

    connect(sck_imu, SIGNAL(readyRead()), this, SLOT(readImu()));
    connect(sck_imu, SIGNAL(disconnected()), this, SLOT(disImu()));
    connect(sck_imu, SIGNAL(connected()), this, SLOT(conImu()));

    connect(sck_sonar, SIGNAL(readyRead()), this, SLOT(readSonar()));
    connect(sck_sonar, SIGNAL(disconnected()), this, SLOT(disSonar()));
    connect(sck_sonar, SIGNAL(connected()), this, SLOT(conSonar()));
}

void comm::disconnect_system()
{
    if(sck_lidar->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        sck_lidar->disconnect();
    }
    if(sck_cam->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        sck_cam->disconnect();
    }
    if(sck_sonar->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        sck_sonar->disconnect();
    }
    if(sck_imu->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        sck_imu->disconnect();
    }
}

void comm::connect_cam(QString strIP, QString strPort)
{
    QHostAddress host(strIP);
    sck_cam->connectToHost(host, strPort.toUShort());

    qDebug() << Q_FUNC_INFO << "CAM 서버 접속 요청";
}

void comm::connect_lidar(QString strIP, QString strPort)
{
    QHostAddress host(strIP);
    sck_lidar->connectToHost(host, strPort.toUShort());

    qDebug() << Q_FUNC_INFO << "LIDAR 서버 접속 요청";
}

void comm::connect_sonar(QString strIP, QString strPort)
{
    QHostAddress host(strIP);
    sck_sonar->connectToHost(host, strPort.toUShort());

    qDebug() << Q_FUNC_INFO << "CAM 서버 접속 요청";
}

void comm::connect_imu(QString strIP, QString strPort)
{
    QHostAddress host(strIP);
    sck_imu->connectToHost(host, strPort.toUShort());

    qDebug() << Q_FUNC_INFO << "IMU 서버 접속 요청";
}


void comm::readLidar()
{
    if(sck_lidar->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = sck_lidar->readAll();
        QString strRecv(readData);
        //qDebug() << "LIDAR : " << strRecv;

        int iStartPos = strRecv.indexOf("[", 0, Qt::CaseInsensitive);
        int iEndPos = strRecv.indexOf("]", 0, Qt::CaseInsensitive);
        if(iStartPos > -1)
        {
            if(iEndPos <= iStartPos)
            {
                // 오류 데이터 버림
            }
            else
            {
                QString strMid = strRecv.mid(iStartPos+1, iEndPos - iStartPos - 1);
                strMid.remove(0,1);
                QStringList listRad = strRecv.split("|");
                for(int i = 0; i < listRad.count(); i++)
                {
                    QString strRad = listRad[i].mid(4, listRad[i].length());
                    common::GetInstance().lidar_iDist[i] = strRad.toInt();
                }
            }
        }
    }
}

void comm::conLidar()
{
    qDebug() << Q_FUNC_INFO << "Lidar 서버 접속 완료.";
}

void comm::disLidar()
{
    sck_lidar->close();
    qDebug() << Q_FUNC_INFO << "Lidar 서버 접속 종료.";
}

void comm::readCam()
{
    if(sck_cam->bytesAvailable() >= 0)
    {
        // 영상값 수신
        QByteArray readData = sck_cam->readAll();
        common::GetInstance().imgbyte.append(readData);
        if(common::GetInstance().imgbyte.count() >= 480 * 640 * 3)
        {
            cv::Mat tmp(480, 640, CV_8UC3,  common::GetInstance().imgbyte.data());
            cv::cvtColor(tmp, tmp, CV_BGR2RGB);
            common::GetInstance().img = tmp.clone();
            common::GetInstance().imgbyte.remove(0, 480 * 640 * 3);
        }
    }
}

void comm::conCam()
{
    qDebug() << Q_FUNC_INFO << "CAM 서버 접속 완료.";
}

void comm::disCam()
{
    sck_cam->close();
    qDebug() << Q_FUNC_INFO << "CAM 서버 접속 종료.";
}

void comm::readImu()
{
    if(sck_imu->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = sck_imu->readAll();
        QString strRecv(readData);
        strRecv.remove("\r\n").remove("#YPR=");
        QStringList strRecvArray = strRecv.split(",");
        //qDebug() << strRecvArray;

        if(strRecvArray.count() == 3)
        {
            common::GetInstance().imu_Yaw = (common::GetInstance().imu_Yaw + static_cast<int>(strRecvArray[0].toFloat()));
            emit send_YPR(strRecvArray[0].toFloat(), strRecvArray[1].toFloat(), strRecvArray[2].toFloat());
        }
    }
}

void comm::conImu()
{
    qDebug() << Q_FUNC_INFO << "IMU 서버 접속 완료.";
}

void comm::disImu()
{
    sck_imu->close();
    qDebug() << Q_FUNC_INFO << "IMU 서버 접속 종료.";
}

void comm::readSonar()
{
    if(sck_sonar->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = sck_sonar->readAll();
        QString strRecv(readData);
        qDebug() << strRecv;

        common::GetInstance().iSonarDist_in = strRecv.mid(1, 3).toInt();
        common::GetInstance().iSonarDist_cm = common::GetInstance().iSonarDist_in * 2.54;
    }
}

void comm::conSonar()
{
    qDebug() << Q_FUNC_INFO << "SONAR 서버 접속 완료.";
}

void comm::disSonar()
{
    sck_sonar->close();
    qDebug() << Q_FUNC_INFO << "SONAR 서버 접속 종료.";
}
