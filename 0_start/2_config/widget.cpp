#include "widget.h"

#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>
#include <QProgressBar>
#include <QTextBrowser>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QSlider>
#include <QScrollBar>
#include <QDial>
#include <QTime>
#include <QDate>
#include <QSlider>
#include <QStyleFactory>

#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400,380);

    label = new QLabel(this);
    label->setGeometry(10, 10, 400, 20);
    label->setText(QString("SYSTEM ON : %1 %2").arg(QDate::currentDate().toString("yyyy.dd.MM"))
                                               .arg(QTime::currentTime().toString("hh시 mm분 ss초 zzz")));

    line = new QLineEdit(this);
    line->setGeometry(10, 40, 170, 20);
    line->setEchoMode(QLineEdit::Password);
    line->setPlaceholderText("input the password");

    QLabel *preset = new QLabel("Preset :", this);
    combo = new QComboBox(this);
    preset->setGeometry(190, 40, 100, 20);
    combo->setGeometry(260, 40, 100, 20);
    combo->addItem("UserSet1");
    combo->addItem("UserSet2");
    combo->addItem("UserSet3");

    QLabel *mode = new QLabel("차량모드 선택 :", this);
    radio[0] = new QRadioButton("일반", this);
    radio[1] = new QRadioButton("연비", this);
    radio[2] = new QRadioButton("스포츠", this);
    mode->setGeometry(10, 70, 100, 20);
    radio[0]->setGeometry(120, 70, 60, 20);
    radio[1]->setGeometry(180, 70, 60, 20);
    radio[2]->setGeometry(240, 70, 60, 20);
    radio[0]->setChecked(true);

    QLabel *mile = new QLabel("누적 주행거리 :", this);
    lcd = new QLCDNumber(this);
    mile->setGeometry(10, 100, 100, 20);
    lcd->setGeometry(120, 100, 100, 20);
    lcd->setDecMode();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->display(55782);

    QLabel *oil = new QLabel("남은 연료 :", this);
    pbar = new QProgressBar(this);
    oil->setGeometry(10, 130, 100, 20);
    pbar->setGeometry(120, 130, 100, 20);
    pbar->setValue(24);
    pbar->setTextVisible(true);

    QLabel *option = new QLabel("옵션 ON/OFF :", this);
    check[0] = new QCheckBox("핸들열선", this);
    check[1] = new QCheckBox("앞차감지", this);
    check[2] = new QCheckBox("차체제어", this);
    option->setGeometry(10, 160, 100, 20);
    check[0]->setGeometry(120, 160, 80, 20);
    check[1]->setGeometry(200, 160, 80, 20);
    check[2]->setGeometry(280, 160, 80, 20);

    QLabel *temp = new QLabel("내부온도 :", this);
    QLabel *tempset = new QLabel("0", this);
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setStyle(QStyleFactory::create("Fusion"));
    temp->setGeometry(10, 190, 100, 20);
    slider->setGeometry(120, 190, 100, 20);
    tempset->setGeometry(230, 190, 50, 20);

    QLabel *vol = new QLabel("볼륨 :", this);
    QLabel *volset = new QLabel("0", this);
    dial = new QDial(this);
    vol->setGeometry(10, 220, 100, 20);
    dial->setGeometry(120, 220, 100, 100);
    volset->setGeometry(50, 220, 50, 20);
    dial->setWrapping(true);
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);

    btn = new QPushButton("설정완료", this);
    btn->setGeometry(10, 330, 70, 40);
}

Widget::~Widget()
{
}

