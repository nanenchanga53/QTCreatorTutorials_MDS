#include "camera_widget.h"
#include "ui_camera_widget.h"
#include<QHostAddress>
#include<QtDebug>
#include <QTime>


Camera_Widget::Camera_Widget(QWidget *parent, lidar_Widget *lidar) :
    QWidget(parent),
    ui(new Ui::Camera_Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));
    initialize();
    ptr_lidar = lidar;
}

Camera_Widget::~Camera_Widget()
{
    delete ui;
}

void Camera_Widget::initialize()
{
    tcpSocket = new QTcpSocket(this);

    //소켓연결로 시그널과 슬롯을 연결시킨다
    connect(tcpSocket, SIGNAL(readyRead()),
            this,      SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),
            this,      SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()),
            this, SLOT(connetecd()));
}

void Camera_Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();
    QString serverPort = ui->portNum->text().trimmed();
    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, serverPort.toUInt());
    qDebug() << "serverip : " << serverip << '\n' << "serverPort : " << serverPort;

}

void Camera_Widget::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 영상값 수신
        QByteArray readData = tcpSocket->readAll();
        imgByte.append(readData);

        if(imgByte.count() >= 480 * 640 * 3)
        {
            cv::Mat tmp(480, 640, CV_8UC3, imgByte.data());
            img = tmp.clone();
            imgByte.remove(0, 480*640*3);




            for(int i = 0 ; i<160; i++)
            {
                int iRadDist = i + 180;
                cv::Scalar color;
                if(ptr_lidar->iDist_Buf[iRadDist] > 500)
                {
                    color = cv::Scalar(0, 0, 255);
                    qDebug() << i << " BLUE\n";
                }
                else if(ptr_lidar->iDist_Buf[iRadDist] > 200)
                {
                    color = cv::Scalar(255, 255, 0);
                    qDebug() << i << " YELLOW\n";
                }
                else if(ptr_lidar->iDist_Buf[iRadDist] > 10)
                {
                    color = cv::Scalar(255, 0, 0);
                    qDebug() << i << " RED";
                }

                cv::line(img, cv::Point(640-i*4,
                        tmp.size().height / 2), cv::Point(640-i*4,
                                   tmp.size().height / 2), color, 2);

            }

            QImage image( img.data,
                          img.cols, img.rows,
                          static_cast<int>(img.step),
                          QImage::Format_RGB888 );

            ui->sensor->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void Camera_Widget::connetecd()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";

}

void Camera_Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

