#include "widget.h"

#include <QLabel>
#include <QTimerEvent>


#include <QTimer>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
    label = new QLabel("Timer", this);
    label->resize(200,100);

    //int id1 = startTimer(50);
    //int id2 = startTimer(1000);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayClock()));
    timer->start(1000);
}

Widget::~Widget()
{
}

void Widget::timerEvent(QTimerEvent* event)
{
    label->setText(QString::number(event->timerId()));
}


void Widget::displayClock()
{
    label->setText(QTime::currentTime().toString());
}
