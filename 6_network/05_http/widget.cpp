#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork/QNetworkAccessManager>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrlQuery>
#include <QUrl>

#include <QJsonValue>
#include <QJsonValueRef>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QNetworkRequest request(QUrl("http://127.0.0.1/api.php")); // json 테스트 주소 http://127.0.0.1/json.php
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray data;
    QUrlQuery paramsquery;
    QUrl params;

    paramsquery.addQueryItem("PID","123456-7896321A");
    paramsquery.addQueryItem("apiKey","userid_api_33239b");
    params.setQuery(paramsquery);

    data.append(params.toString());
    data.remove(0,1);

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    manager->post(request,data);

    //Get 방식이용
    //request.setUrl(QUrl("http://127.0.0.1/api.php?PID=10003020&apiKey=userGetApiKey"));
    //manager->get(request);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::httpPost()
{
}

void Widget::replyFinished(QNetworkReply *pNetworkReply)
{
    QNetworkReply::NetworkError err = pNetworkReply->error();
    QByteArray rtnAPI;
    if ( err == QNetworkReply::NoError )
    {
        rtnAPI = pNetworkReply->readAll();
        qDebug() << rtnAPI;

//        QJsonDocument jsonDoc(QJsonDocument::fromJson(rtnAPI));
//        QJsonObject jsonReply = jsonDoc.object();

//        QJsonObject response = jsonReply["response"].toObject();
//        QJsonArray  data     = jsonReply["data"].toArray();
//        qDebug() << data;

    }
    pNetworkReply->deleteLater();
}
