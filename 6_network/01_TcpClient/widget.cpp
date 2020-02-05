#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, SIGNAL(clicked()),
            this,              SLOT(connectButton()));

    initialize();
}

void Widget::initialize()
{
    tcpSocket = new QTcpSocket(this);

    //소켓연결로 시그널과 슬롯을 연결시킨다
    connect(tcpSocket, SIGNAL(readyRead()),
            this,      SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),
            this,      SLOT(disconnected()));
}

void Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();

    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, 25000);
}

void Widget::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0) //바이트로 데이터를 읽는다
    {
        QByteArray readData = tcpSocket->readAll(); //큰 데이터가 들어올때는 잘라서 쓰도록 변경하자
        ui->textEdit->append(readData);
    }
}

void Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

Widget::~Widget()
{
    delete ui;
}

