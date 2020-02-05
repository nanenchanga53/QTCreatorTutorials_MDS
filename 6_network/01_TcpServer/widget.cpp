#include "widget.h"
#include "ui_widget.h"

#include <QtWidgets>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    initialize();
}

void Widget::initialize()
{
    QHostAddress hostAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // localhost(127.0.0.1) 가 아닌 것을 사용
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        qDebug() << ipAddressesList.at(i);
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            hostAddress = ipAddressesList.at(i);
            break;
        }
    }

    if (hostAddress.toString().isEmpty())
        hostAddress = QHostAddress(QHostAddress::LocalHost);

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(hostAddress, 25000)) {
        QMessageBox::critical(this, tr("TCP Server"),
                              tr("서버를 시작할 수 없습니다. 에러메세지 : %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    ui->labelStatus->setText(tr("서버 동작 중 \n\n"
                                "IP : %1\n"
                                "PORT : %2\n")
                         .arg(hostAddress.toString())
                             .arg(tcpServer->serverPort()));

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

    ui->connMsgEdit->clear();
}

void Widget::newConnection()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    QString currTime = QTime::currentTime().toString("hh시 mm분 ss초");
    QString text = QString("클라이언트 접속 (%1)").arg(currTime);

    ui->connMsgEdit->append(text);
    QByteArray message = QByteArray("Hello Client ~ ");
    clientConnection->write(message);
    clientConnection->disconnectFromHost();
}

Widget::~Widget()
{
    delete ui;
}
