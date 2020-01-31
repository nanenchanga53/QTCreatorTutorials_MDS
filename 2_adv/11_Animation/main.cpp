#include "widget.h"

#include <QApplication>

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 40, 20);
    QGraphicsRectItem *rect2 = new QGraphicsRectItem(200, 0, 40, 20);
    rect->setBrush(QBrush(Qt::blue));
    rect2->setBrush(QBrush(Qt::red));

    QTimeLine *timer = new QTimeLine(5000);//총시간 5초
    timer->setFrameRange(0, 10);//프레임개수

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(rect);
    animation->setTimeLine(timer);

    QGraphicsItemAnimation *animation2 = new QGraphicsItemAnimation;
    animation2->setItem(rect2);
    animation2->setTimeLine(timer);

    //이동할 포지션 등록
    for(int i=0; i<200; ++i)
    {
        animation->setPosAt(i/200.0, QPointF(i,i));
    }
    animation->setRotationAt(80.0/200.0, 30);//회전
    animation->setRotationAt(180.0/200.0, 90);

    for(int i = 199; i>= 0; --i)
    {
        animation2->setPosAt(i/200.0, QPointF(i,i));
    }
    animation2->setRotationAt(30, 80.0/200.0);
    animation2->setRotationAt(180.0/200.0,90);


    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,400,400);
    scene->addItem(rect);
    scene->addItem(rect2);

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
    timer->start();

    return a.exec();
}
