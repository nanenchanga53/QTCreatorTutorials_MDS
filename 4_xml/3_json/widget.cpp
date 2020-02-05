#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << Q_FUNC_INFO;

    QFile file("../sample.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file.";
            return;
    }

    QString data = file.readAll();
    file.close();



    QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toLocal8Bit());
    QJsonObject jsonObj = jsonResponse.object();

    qDebug() << jsonObj["time"].toString().append("\n");
    qDebug() << jsonObj["date"].toString().append("\n");

    if(jsonObj["success"].toBool() == true)
        qDebug() << QString("success : true \n");
    else
        qDebug() << QString("success : false \n");

    QJsonArray jsonArray = jsonObj["properties"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        QString property = obj["PropertyName"].toString();
        QString key      = obj["key"].toString();

        QString arrayData;
        arrayData = QString("property : %1 , key : %2 \n")
                                .arg(property).arg(key);

        qDebug() << arrayData;
    }
}

Widget::~Widget()
{
    delete ui;
}

