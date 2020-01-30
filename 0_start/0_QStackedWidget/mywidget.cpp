#include "mywidget.h"

#include <QStackedLayout>
#include <QPushButton>
#include <QDebug>

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400,400);

    QWidget *WidgetP1 = new QWidget;
    WidgetP1->resize(100,100);
    QWidget *WidgetP2 = new QWidget;
    WidgetP2->resize(200,200);
    QWidget *WidgetP3 = new QWidget;
    WidgetP3->resize(250,250);
    QPushButton *WidgetP1_btn = new QPushButton("1page", WidgetP1);
    WidgetP1_btn->setGeometry(10,10,100,100);
    QPushButton *WidgetP2_btn = new QPushButton("2page", WidgetP2);
    WidgetP2_btn->setGeometry(30,30,100,100);
    QPushButton *WidgetP3_btn = new QPushButton("3page", WidgetP3);
    WidgetP3_btn->setGeometry(50,50,100,100);

    StackedLayout = new QStackedLayout(this);
    StackedLayout->addWidget(WidgetP1);
    StackedLayout->addWidget(WidgetP2);
    StackedLayout->addWidget(WidgetP3);

    connect(WidgetP1_btn, SIGNAL(clicked()), this, SLOT(setPage1()));
    connect(WidgetP2_btn, SIGNAL(clicked()), this, SLOT(setPage2()));
    connect(WidgetP3_btn, SIGNAL(clicked()), this, SLOT(setPage3()));

    char a;
    a = '1';

    QString b;
    b = "abc";

    std::string c;
    c = "asdf";

    qDebug() << a;
    qDebug() << b;
    qDebug() << c.c_str();
}

myWidget::~myWidget()
{
}

void myWidget::setPage1()
{
    StackedLayout->setCurrentIndex(1);
}
void myWidget::setPage2()
{
    StackedLayout->setCurrentIndex(2);
}
void myWidget::setPage3()
{
    StackedLayout->setCurrentIndex(0);
}

