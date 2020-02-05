#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "thread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 300);
    QLabel* label = new QLabel(this);
    label->resize(100,100);
    th = new Thread(label);

    QPushButton* stopbtn = new QPushButton("STOP", this);
    QPushButton* resumebtn = new QPushButton("RESUME", this);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(stopbtn);
    hlayout->addWidget(resumebtn);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(label);
    vlayout->addLayout(hlayout);

    connect(stopbtn, SIGNAL(clicked()), th, SLOT(stopThread()));
    connect(resumebtn, SIGNAL(clicked()), th, SLOT(resumeThread()));
    connect(th, SIGNAL(setLabeled(QString)), label, SLOT(setText(QString)));

    setLayout(vlayout);

    th->start();

    RunnableTask *runTh = new RunnableTask();
    QThreadPool::globalInstance()->start(runTh);
}

Widget::~Widget()
{
    th->terminate();
}

