#include "widget.h"
#include <QLabel>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel("abc",this);

    label->resize(100,100);
    label -> show();//좌상의 엄청 작게 뜰 것이다

    QPushButton *push = new QPushButton("btn",this);
    push->resize(50,50);
    push->show();

    //푸시버튼에 클릭 이벤트 시그널이 발생하면 종료
    QObject::connect(push,SIGNAL(clicked()),this,SLOT(close()));

    //메인에서 쓰려면 아래와 같이 quit을 쓰자
    //QObject::connect(push,SIGNAL(clicked()),this,SLOT(quit()));
}

Widget::~Widget()
{
}

