#include "widget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

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

    QButtonGroup *buttonGroup = new QButtonGroup(this);

    for(int i = 0; i < 16; i++)
    {
        btn[i] = new QPushButton(BtnChar[i], this);
        gridLayout->addWidget(btn[i], i/4, i%4);
        buttonGroup->addButton(btn[i], i);
    }

    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(clickedGroup(int))); // 7

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

void Widget::clickedGroup(int id)
{
    QPushButton* button = (QPushButton*)((QButtonGroup*)sender())->button(id);

    QString buttonText = button->text();

    switch (id) {
        case 0: case 1: case 2: // 7 8 9
        case 4: case 5: case 6: // 4 5 6
        case 8: case 9: case 10: // 1 2 3
        case 12:
            label->setText((label->text()=="0"?buttonText:label->text()+buttonText));
            break;
        case 3:
            clear();
            break;
        case 7: case 11: case 14: case 15:
            numberTemp = label->text();
            label->setText("0");
            operate = buttonText;
            break;
        case 13:
            calculate();
            break;

    }
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


