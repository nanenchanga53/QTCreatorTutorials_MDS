#include "widget.h"

#include <QState>
#include <QSignalTransition>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    this->resize(500, 500);

    QPushButton *btn = new QPushButton("Button", this);
    connect(btn, &QPushButton::pressed,
            this, &Widget::btnClicked);
    btn->setGeometry(10, 10, 100, 30);

    animation = new QPropertyAnimation(btn, "geometry", this);

    animation->setDuration(3000); // 3초(단위 밀리세컨드)
    animation->setStartValue(QRect(10, 10, 100, 30)); // 시작 좌표
    animation->setEndValue(QRect(200, 150, 100, 30)); // 끝나는 좌표

    animation->setEasingCurve(QEasingCurve::OutInQuart);


    QStateMachine *machine = new QStateMachine;

    QState *state1 = new QState(machine); // state-1
    state1->assignProperty(btn, "geometry", QRect(10, 10, 100, 30));
    machine->setInitialState(state1);

    QState *state2 = new QState(machine); // state-2
    state2->assignProperty(btn, "geometry", QRect(250, 250, 100, 30));

    QSignalTransition *transition1 = state1->addTransition(btn,
                                SIGNAL(clicked()), state2); // transition-1
    transition1->addAnimation(new QPropertyAnimation(btn, "geometry"));

    QSignalTransition *transition2 = state2->addTransition(btn,
                                SIGNAL(clicked()), state1); // transition-2
    transition2->addAnimation(new QPropertyAnimation(btn, "geometry"));

    machine->start();
}

void Widget::btnClicked()
{
    animation->start();
}

Widget::~Widget()
{
}


