#include "widget.h"
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QStyleFactory>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDial>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400,400);

    mQSpinBox();
    mQSlider();
    mQRadioButton();
    mQDial();
}

Widget::~Widget()
{
}

//스핀박스 (숫자 위아래로)
void Widget::mQSpinBox()
{
    QSpinBox *sBox = new QSpinBox(this);
    sBox->setRange(0,10); //0~10
    sBox->setWrapping(true);
    sBox->setGeometry(0,50,50,50);
    sBox->setSpecialValueText("Hi"); //시작 문자
}

//슬라이더
void Widget::mQSlider()
{
    QSlider *slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);//가로 슬라이더
    slider->setTickPosition(QSlider::TicksAbove);//점선 찍는 형태를 위에
    slider->setStyle(QStyleFactory::create("Fusion"));//퓨전 스타일

}

void Widget::mQRadioButton()
{

}

//아날로그 다이얼(원형 360도)
void Widget::mQDial()
{
    QDial *dial = new QDial(this);
    dial->setGeometry(0,150,50,50);
    dial->setWrapping(true);
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);

}
