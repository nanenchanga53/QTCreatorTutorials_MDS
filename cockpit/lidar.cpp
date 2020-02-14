#include "lidar.h"
#include "ui_lidar.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QPainter>

#include <QTime>

lidar::lidar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lidar)
{
    ui->setupUi(this);
    initialize();
}

lidar::~lidar()
{
    delete ui;
}

void lidar::initialize()
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));


    for(int i=0; i<360; i++)
    {
        iDist[i] = 0;
    }
}

void lidar::connectButton()
{
    QString sensorip   = ui->sensorip->text().trimmed();
    QString sensorport   = ui->sensorport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void lidar::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
    startTimer(1000);
}

void lidar::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = tcpSocket->readAll();
        QString strRecv(readData);
        qDebug() << strRecv;
//        ui->value->setText("현재시간 : " + QTime::currentTime().toString() + " = " + strRecv);

//        if(strRecv.indexOf("t:", 0, Qt::CaseInsensitive) > -1 && strRecv.indexOf("d:", 0, Qt::CaseInsensitive) > -1)
//        {
//            strRecv.remove("\n").remove("t:").remove("d:");
//            QStringList strRecvArray = strRecv.split(",");
//            int iTheta = strRecvArray[0].toInt();
//            int iDistance = strRecvArray[1].toInt();

//            iDist[iTheta] = iDistance;
//        }

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
                qDebug() << strMid;
                strMid.remove(0,1);
                QStringList listRad = strRecv.split("|");

                for(int i = 0; i < listRad.count(); i++)
                {
                    QString strRad = listRad[i].mid(4, listRad[i].length());
                    iDist[i] = strRad.toInt();
                }
            }
        }
    }
}

void lidar::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

void lidar::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    painter->translate(width()/2, ui->sensor->y() + ui->sensor->height() / 2);

    painter->setPen(QPen(Qt::blue, 5));
    painter->drawPoint(0, 0);

    painter->setPen(QPen(Qt::red, 5));
    for(int i=0; i<360; i++)
    {
        if(iDist[i] != 0)
        {
            painter->drawPoint(iDist[i] / 10, 0);
            iDist[i] = 0;
        }
        painter->rotate(-1);
    }

    delete painter;
}

void lidar::timerEvent(QTimerEvent* event)
{
    update();
}
