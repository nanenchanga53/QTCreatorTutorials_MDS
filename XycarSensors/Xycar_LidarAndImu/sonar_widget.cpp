#include "sonar_widget.h"
#include "ui_sonar_widget.h"
#include<QHostAddress>
#include<QtDebug>
#include <QTime>
#include <QPainter>


Sonar_Widget::Sonar_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sonar_Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));
    initialize();
}

Sonar_Widget::~Sonar_Widget()
{
    delete ui;
}

void Sonar_Widget::initialize()
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

void Sonar_Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();
    QString serverPort = ui->portNum->text().trimmed();
    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, serverPort.toUInt());
    qDebug() << "serverip : " << serverip << '\n' << "serverPort : " << serverPort;

}

void Sonar_Widget::readMessage()
{

    if(tcpSocket->bytesAvailable() >= 0) //바이트로 데이터를 읽는다
    {
        QByteArray readData = tcpSocket->readAll(); //큰 데이터가 들어올때는 잘라서 쓰도록 변경하자
        QString strRecv(readData);
        strRecv.remove("\r");
        QStringList strRecvList = strRecv.split(" ");

        ui->textEdit->append(strRecv);
        strRecvList[0].remove(0,1);

        recvLen = strRecvList[0].toInt();
        recvLen_cm = recvLen * 2.5;

        if(strRecvList[1] == "P1")
        {

            ui->SonarData->setText(QString("%1in %2cm").arg(recvLen).arg(recvLen_cm));
            if(recvLen_cm  < 30)
            {
                strMsg = "접촉 주의";
            }
            else if(recvLen_cm < 60)
            {
                strMsg = "근거리 접근";
            }
            else
            {
                strMsg = "";
            }
            update();
        }
    }

}

void Sonar_Widget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->translate(width()/2, ui->sensor->y() + 30);
    QRect rectangle(-150, -300 + 20, 300, 600);
    int startAngle = 5760 / 4 * -1 + 16 * 30 * -1;
    int spanAngle = 16 * 30 * 2;
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(QBrush(Qt::white));
    painter->drawPie(rectangle, startAngle, spanAngle);
    painter->setPen(QPen(Qt::blue, 10));
    painter->drawPoint(0, 0);
    // 152.2cm
    painter->setPen(QPen(Qt::red, 1));
    if(recvLen_cm > 152)
    {
        recvLen_cm = 152;
    }
    painter->drawLine(-150, recvLen_cm * 2 + 20, 150, recvLen_cm * 2 + 20);
    painter->drawText(50, 0, strMsg);
    QRect clipRect(-150, 20, 300, recvLen_cm * 2);
    painter->setClipping(true);
    painter->setClipRect(clipRect);
    painter->setBrush(QBrush(Qt::red));
    painter->drawPie(rectangle, startAngle, spanAngle);
    delete painter;
}


void Sonar_Widget::connetecd()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";

}

void Sonar_Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

