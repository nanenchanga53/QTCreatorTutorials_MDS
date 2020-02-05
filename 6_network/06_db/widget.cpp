#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << QCoreApplication::libraryPaths();
    qDebug() << QSqlDatabase::drivers()<<endl;
    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL"));
    db.setHostName("127.0.0.1");
    db.setDatabaseName("QT");
    db.setUserName("root");
    db.setPassword("1234");
    if (!db.open())
    {
        qDebug() << "NO" << endl;
    }
    else
    {
       qDebug() << "OK" << endl;
    }

    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("SELECT * FROM CAR");
    query.exec();
    while(query.next())
    {
        qDebug() << query.value(0);
        qDebug() << query.value(1);
    }
}

Widget::~Widget()
{
    delete ui;
}

