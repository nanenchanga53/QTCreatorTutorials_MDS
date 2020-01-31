#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(400, 400);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    paint1();
    //paint2();
    //paint3();
}

void Widget::paint1()
{
    QPainter *painter = new QPainter(this);

    painter->setPen(QPen(Qt::blue, 4, Qt::DashLine));
    painter->drawPoint(10, 10);


    painter->drawLine(20, 20, 100, 100);

    painter->drawRect(120, 120, 80, 80);

    painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine));

    painter->drawRoundRect(200, 20, 60, 60, 80);
    painter->drawRoundRect(300, 20, 60, 60);

    painter->drawArc(20, 300, 80, 80, 30 * 16, 150 * 16);
    painter->drawChord(120, 300, 80, 80, 30 * 16, 150 * 16);
    painter->drawPie(220, 300, 80, 80, 30 * 16, 150 * 16);

    painter->drawEllipse(320, 300, 30, 30);

    static const QPoint points[6] = {
        QPoint(20, 20),
        QPoint(20, 90),
        QPoint(90, 80),
        QPoint(80, 160),
        QPoint(160, 28),
        QPoint(80, 120),
    };

    painter->drawPolygon(points, 6);


    painter->drawText(250, 10, "PaintEvent Painting");
    delete painter;
}

void Widget::paint2()
{
    QPainterPath path;
    path.addRect(20, 20, 60, 60);

    path.moveTo(0, 0);
    path.cubicTo(99, 0, 50, 50, 99, 99);
    path.cubicTo(0, 99, 50, 50, 0, 0);


    QPainter *painter = new QPainter(this);

    painter->fillRect(0, 0, 100, 100, Qt::white);

    painter->setPen(QPen(QColor(79, 106, 25), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122,163,39));

    painter->drawPath(path);

    delete painter;
}


void Widget::paint3()
{
    QRectF target(10.0, 20.0, 80.0, 60.0);
    QRectF source(0.0, 0.0, 70.0, 40.0);
    QPixmap pixmap("../../../image/icon1.png");
    QPixmap pixmap2("../../../image/icon2.png");

    QPainter *painter = new QPainter(this);

    painter->drawPixmap(10, 10, pixmap2.width(), pixmap2.height(), pixmap2);
    painter->drawPixmap(target, pixmap, source);

    QImage img("../../../image/Cluster1.png");
    painter->drawImage(100,100, img, 20, 20, 100, 100);
    delete painter;
}

