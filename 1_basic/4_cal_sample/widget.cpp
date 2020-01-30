#include "widget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const char BtnChar[16][2] = {
        "7", "8", "9", "C",
        "4", "5", "6", "/",
        "1", "2", "3", "*",
        "0", "=", "+", "-"
    };

    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight);
    label->setFrameShape(QFrame::Box);

    QPushButton* btn[16];
    QGridLayout* gridLayout = new QGridLayout();

    for(int i = 0; i < 16; i++)
    {
        btn[i] = new QPushButton(BtnChar[i], this);
        gridLayout->addWidget(btn[i], i/4, i%4);
    }

    connect(btn[0], SIGNAL(clicked()), SLOT(setNum())); // 7
    connect(btn[1], SIGNAL(clicked()), SLOT(setNum())); // 8
    connect(btn[2], SIGNAL(clicked()), SLOT(setNum())); // 9
    connect(btn[3], SIGNAL(clicked()), SLOT(operation())); // C

    connect(btn[4], SIGNAL(clicked()), SLOT(setNum())); // 4
    connect(btn[5], SIGNAL(clicked()), SLOT(setNum())); // 5
    connect(btn[6], SIGNAL(clicked()), SLOT(setNum())); // 6
    connect(btn[7], SIGNAL(clicked()), SLOT(operation())); // /

    connect(btn[8], SIGNAL(clicked()), SLOT(setNum())); // 1
    connect(btn[9], SIGNAL(clicked()), SLOT(setNum())); // 2
    connect(btn[10], SIGNAL(clicked()), SLOT(setNum())); // 3
    connect(btn[11], SIGNAL(clicked()), SLOT(operation())); // *

    connect(btn[12], SIGNAL(clicked()), SLOT(setNum())); // 0
    connect(btn[13], SIGNAL(clicked()), SLOT(calculate())); // =
    connect(btn[14], SIGNAL(clicked()), SLOT(operation())); // +
    connect(btn[15], SIGNAL(clicked()), SLOT(operation())); // -

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setMargin(6);
    vBoxLayout->addWidget(label);
    vBoxLayout->addLayout(gridLayout);
    setLayout(vBoxLayout);
}

Widget::~Widget()
{
    delete label;
}

void Widget::setNum()
{
    // 문자로 취급
    QString result = (label->text()=="0")?
                            ((QPushButton*)sender())->text()
                            :label->text() + ((QPushButton*)sender())->text();
    label->setText(result);
    // 숫자로 취급
    //label->setText(QString::number(label->text().toFloat()*10 + \
                                   ((QPushButton*)sender())->text().toFloat()));
}



void Widget::operation()
{
    numberTemp = label->text();
    operate = ((QPushButton*)sender())->text();
    label->setText("0");
}

void Widget::calculate()
{
    float result;
    switch(operate.at(0).toLatin1()){
        case '+':
            result = numberTemp.toFloat() + label->text().toFloat();
            break;
        case '-':
            result = numberTemp.toFloat() - label->text().toFloat();
            break;
        case '*':
            result = numberTemp.toFloat() * label->text().toFloat();
            break;
        case '/':
            if(label->text().toFloat() > 0)
            {
                result = numberTemp.toFloat() / label->text().toFloat();
            }
            else
            {
                label->setText("Err : Cannot Divide by Zero");
                result = 0;
            }

            break;
    }
    label->setText(QString::number(result));
}

void Widget::clear()
{
    numberTemp.setNum(0);
    label->setText("0");
}


