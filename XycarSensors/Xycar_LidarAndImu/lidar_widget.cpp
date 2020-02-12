#include "lidar_widget.h"
#include "ui_lidar_widget.h"
#include "lidarpaint.h"
#include<QHostAddress>
#include<QtDebug>
#include<QTime>

lidar_Widget::lidar_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lidar_Widget)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));

    objpaint = new LidarPaint(ui->sensor);
    objpaint->resize(ui->sensor->width(), ui->sensor->height());

    initialize();
}

lidar_Widget::~lidar_Widget()
{
    delete ui;
}

void lidar_Widget::initialize()
{
    tcpSocket = new QTcpSocket(this);

    //소켓연결로 시그널과 슬롯을 연결시킨다
    connect(tcpSocket, SIGNAL(readyRead()),
            this,      SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),
            this,      SLOT(disconnected()));
    connect(ui->lineEditAngle,SIGNAL(textChanged(const QString &)),objpaint,SLOT(ChangeAngle(const QString &)));

    for(int i = 0; i< 360; i++)
    {
        iDist[i] = 0;
        iDist_Buf[i]=0;
    }
}

void lidar_Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();
    QString serverPort = ui->portNum->text().trimmed();
    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, serverPort.toUInt());
    qDebug() << "serverip : " << serverip << '\n' << "serverPort : " << serverPort;

}

void lidar_Widget::readMessage()
{
    QString strRecvs;
    if(tcpSocket->bytesAvailable() >= 0) //바이트로 데이터를 읽는다
    {
        QByteArray readData = tcpSocket->readAll(); //큰 데이터가 들어올때는 잘라서 쓰도록 변경하자
        QString strRecv(readData),strDump;
        strRecvs.append(strRecv);
        int startAt = strRecvs.indexOf("[",Qt::CaseSensitive);
        int lastAt = strRecvs.indexOf("]",Qt::CaseSensitive);

        if(lastAt > 0)
        {
            strDump = strRecvs.mid(startAt,lastAt-startAt+1);
            strRecvs.remove(0,strDump.length());
            strDump.remove("[",Qt::CaseSensitive);
            strDump.remove("]",Qt::CaseSensitive);
            strDump.remove(0,1);
        }

        if(strDump.length() != 0)
        {
            QStringList strRecvArray = strDump.split("|");
            if(strRecvArray.count() != 360)
                return;
            ui->textEdit->append("------------------------\n");
            ui->textEdit->append(strDump);
            ui->textEdit->append("------------------------\n");


            for(int i = 0; i< strRecvArray.count();i++)
            {
                QStringList recvData;
                recvData = strRecvArray[i].split("_");
                iDist[i] = recvData[1].toInt();
                iDist_Buf[i] = recvData[1].toInt();
                objpaint->drawPoint(i,iDist[i]);
            }
            objpaint->update();

        }


    }
}

void lidar_Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

void lidar_Widget::recvYaw(int numYaw)
{
    ui->LabelYAW->setNum(numYaw);
    ui->lineEditAngle->setText(QString::number(numYaw));
    qDebug() << "YAW:" << numYaw;

}

