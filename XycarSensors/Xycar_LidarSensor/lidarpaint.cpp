#include "lidarpaint.h"
#include "ui_lidarpaint.h"

#include <QPainter>
#include <QPaintEvent>

lidarPaint::lidarPaint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lidarPaint)
{
    ui->setupUi(this);

}

lidarPaint::~lidarPaint()
{
    delete ui;
}

void lidarPaint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);

    background = QBrush(QColor(255, 255, 255));
    circlePen = QPen(Qt::black);
    circlePen.setWidth(10);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(10);



    painter.setBrush(circleBrush);
    painter.setPen(circlePen);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1));

    int smallR=40,mediamR=100,largeR=200;
    painter.drawEllipse(this->size().width()/2 - (smallR/2),this->size().height()/2 - (smallR/2),smallR,smallR);
    painter.drawEllipse(this->size().width()/2 - (mediamR/2),this->size().height()/2 - (mediamR/2),mediamR,mediamR);
    painter.drawEllipse(this->size().width()/2 - (largeR/2),this->size().height()/2 - (largeR/2),largeR,largeR);

    painter.setPen(textPen);
    painter.setFont(textFont);
    painter.drawText(QRect(this->size().width()/2 - (smallR/2), this->size().height()/2 - (smallR/2), 50, 10), Qt::AlignCenter, QStringLiteral("20mm"));
    painter.drawText(QRect(this->size().width()/2 - (mediamR/2), this->size().height()/2 - (mediamR/2), 50, 10), Qt::AlignCenter, QStringLiteral("50mm"));
    painter.drawText(QRect(this->size().width()/2 - (largeR/2), this->size().height()/2 - (largeR/2), 50, 10), Qt::AlignCenter, QStringLiteral("100mm"));


    painter.save();

}

//! [1]
void lidarPaint::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
//! [2]

}

void lidarPaint::drawPoint(int angle, int length)
{


}
