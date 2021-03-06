#include "imu_widget.h"
#include "imu3d.h"
#include "ui_imu_widget.h"
#include<QHostAddress>
#include<QtDebug>
#include <QTime>

Imu_Widget::Imu_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Imu_Widget)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));

    obj3d = new imu3d(ui->sensor);
    obj3d->resize(ui->sensor->width(), ui->sensor->height());

    initialize();
}

Imu_Widget::~Imu_Widget()
{
    delete ui;
}


void Imu_Widget::initialize()
{
    tcpSocket = new QTcpSocket(this);

    //소켓연결로 시그널과 슬롯을 연결시킨다
    connect(tcpSocket, SIGNAL(readyRead()),
            this,      SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),
            this,      SLOT(disconnected()));
}

void Imu_Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();
    QString serverPort = ui->portNum->text().trimmed();
    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, serverPort.toUInt());
    qDebug() << "serverip : " << serverip << '\n' << "serverPort : " << serverPort;

}

void Imu_Widget::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0) //바이트로 데이터를 읽는다
    {
        QByteArray readData = tcpSocket->readAll(); //큰 데이터가 들어올때는 잘라서 쓰도록 변경하자
        ui->textEdit->append(readData);
        QString strRecv(readData);

        ui->TimeLable->setText(QTime::currentTime().toString());
        ui->YPRLabel->setText(readData);

        strRecv.remove("\r\n").remove("#YPR=");

        QStringList strRecvArray = strRecv.split(",");
        ui->YAWLabel->setText(strRecvArray[0]);
        ui->PITCHLabel->setText(strRecvArray[1]);
        ui->ROLLLabel->setText(strRecvArray[2]);

        obj3d->setXYZRotation(strRecvArray[0].toFloat(), strRecvArray[1].toFloat(), strRecvArray[2].toFloat());

    }
}

void Imu_Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}
