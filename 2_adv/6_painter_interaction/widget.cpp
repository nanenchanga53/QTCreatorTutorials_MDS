#include "widget.h"

#include <QPainter>
#include <QMouseEvent>

#define DEGREE 56.31

int iCircleSize = 1;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 300);

    clipWidth = 0;

    startTimer(20);

    setMouseTracking(true);
}

Widget::~Widget()
{
}

void Widget::timerEvent(QTimerEvent* event)
{
    if(clipWidth < 5000)
    {
        clipWidth++;
        update();
    }
}

// 태극무늬 각도 56.31
void Widget::paintEvent(QPaintEvent *event)
{
    QRect clipRect(0, 0, clipWidth%width()+1, height());

    QPainter painter(this);

    painter.setPen(Qt::red);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(50,50, 30 * iCircleSize, 30 * iCircleSize);

    painter.setClipping(true);
    painter.setClipRect(clipRect);

    painter.setPen(Qt::black);

    qreal diagonalLength = sqrt(pow(width(), 2) + pow(height(), 2));
    qint16 radius = width()/3.;
    qint16 xPoint = (width()-radius)/2., yPoint = (height()-radius)/2.;

    QPainterPath pathBigRed;
    pathBigRed.arcMoveTo(xPoint, yPoint, radius, radius, 180-DEGREE/2);
    pathBigRed.arcTo(xPoint, yPoint, radius, radius, -DEGREE/2, 180);
    painter.setBrush(Qt::red);
    painter.drawPath(pathBigRed);

    QPainterPath pathBigBlue;
    pathBigBlue.arcMoveTo(xPoint, yPoint, radius, radius, 180-DEGREE/2);
    pathBigBlue.arcTo(xPoint, yPoint, radius, radius, 180-DEGREE/2, 180);
    painter.setBrush(Qt::blue);
    painter.drawPath(pathBigBlue);

    painter.setBrush(Qt::red);
    painter.resetMatrix();
    painter.translate(width()/2, height()/2);
    painter.rotate(-DEGREE);
    painter.drawEllipse(-radius/4., -radius/2, radius/2., radius/2.);

    painter.setBrush(Qt::blue);
    painter.resetMatrix();
    painter.translate(width()/2, height()/2);
    painter.rotate(-DEGREE);
    painter.drawEllipse(-radius/4., 0, radius/2., radius/2.);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    resize(this->size().width(), this->size().width()*2/3);
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint position = event->pos();

    if(position.x() >= 50 && position.x() <= 100)
    {
        iCircleSize = 2;
    }
    else
    {
        iCircleSize = 1;
    }
}
