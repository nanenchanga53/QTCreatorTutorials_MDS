#include "ivi.h"
#include "ui_ivi.h"

#include <QWebEngineView>

ivi::ivi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ivi)
{
    ui->setupUi(this);


    // load image
    on = new QPixmap(":/images/off.png");
    off = new QPixmap(":/images/on.png");

    on_icon = new QIcon(*on);
    off_icon = new QIcon(*off);

    ui->start->setIcon(*on_icon);
    ui->start->setIconSize(ui->start->rect().size());

    view = new QWebEngineView(this);
    view->setUrl(QUrl("qrc:/images/map.html"));
    //view->setUrl(QUrl("http://192.168.101.3/test.html"));
    view->setGeometry(100,10,400,500);

    bStart = false;
}

ivi::~ivi()
{
    delete ui;

    delete on;
    delete off;

    delete on_icon;
    delete off_icon;
}

void ivi::on_start_clicked()
{
    if(bStart == true)
    {
        bStart = false;
        emit endSystem();
        ui->start->setIcon(*on_icon);
    }
    else
    {
        bStart = true;
        emit startSystem();
        ui->start->setIcon(*off_icon);
    }
}

void ivi::on_map1_clicked()
{
    view->page()->runJavaScript("moveto(127.0347583,37.4992707);",[this](const QVariant &v)
            {
                qDebug()<<v.toString();
            }
        );
}

void ivi::on_map2_clicked()
{
    view->page()->runJavaScript("moveto(127.0342583,37.4992700);",[this](const QVariant &v)
            {
                qDebug()<<v.toString();
            }
        );

}
