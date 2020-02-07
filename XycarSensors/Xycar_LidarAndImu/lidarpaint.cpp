#include "lidarpaint.h"
#include "ui_lidarpaint.h"
#include <QPainter>
#include <QPaintEvent>
LidarPaint::LidarPaint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LidarPaint)
{
    ui->setupUi(this);
    startAngle = 0;
    for(int i = 0; i< 360;i++)
        iDist[i] = 0;
}

LidarPaint::~LidarPaint()
{
    delete ui;
}

void LidarPaint::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->begin(this);

    painter->translate(this->size().width()/2,this->size().height()/2); //중심점 이동

    background = QBrush(QColor(255, 255, 255));
    circlePen = QPen(Qt::black);
    circlePen.setWidth(10);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(10);

    painter->setPen(QPen(QColor(0,255,0),3));
    painter->rotate(-startAngle);
    painter->drawLine(0,0,0,-100);



    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black, 1));

    painter->drawPoint(0,0);

    int smallR=40,mediamR=100,largeR=200;
    painter->drawEllipse(-smallR/2,-smallR/2,smallR,smallR);
    painter->drawEllipse(-mediamR/2,-mediamR/2,mediamR,mediamR);
    painter->drawEllipse(-largeR/2,-largeR/2,largeR,largeR);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-(smallR/2), -(smallR/2), 50, 10), Qt::AlignCenter, QStringLiteral("20mm"));
    painter->drawText(QRect(-(mediamR/2), -(mediamR/2), 50, 10), Qt::AlignCenter, QStringLiteral("50mm"));
    painter->drawText(QRect(-(largeR/2), -(largeR/2), 50, 10), Qt::AlignCenter, QStringLiteral("100mm"));

    //0-360거리
    painter->setPen(QPen(QColor(255,0,0),3));

    for(int i = 0; i< 360; i++)
    {
        if(iDist[i] != 0)
        {
            painter->drawPoint(iDist[i] / 10, 0);
            iDist[i] = 0;
        }
        painter->rotate(-1);
    }

    painter->rotate(startAngle);
    painter->save();



    delete painter;

}

void LidarPaint::ChangeAngle(QString angle)
{
    startAngle = angle.toInt();
}

//! [1]
void LidarPaint::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
//! [2]

}

void LidarPaint::drawPoint(int angle, int length)
{
    iDist[angle] = length;


}
