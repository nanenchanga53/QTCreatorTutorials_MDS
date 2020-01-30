#include "widget.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    int xpos = 30, ypos = 30;

    this->resize(400, 400);

    chk_group[0] = new QButtonGroup(this);
    chk_group[1] = new QButtonGroup(this);

    chk_group[0]->setExclusive(true);
    chk_group[1]->setExclusive(false);

    connect(chk_group[0], SIGNAL(buttonClicked(int)), this, SLOT(chkChanged(int)));
    connect(chk_group[1], SIGNAL(buttonClicked(int)), this, SLOT(chkChanged_Non(int)));

    for (int i = 0; i < 3; i++)
    {
        exclusive[i] = new QCheckBox(str1[i], this);
        exclusive[i]->setGeometry(xpos, ypos, 100, 30);
        chk_group[0]->addButton(exclusive[i], i);  // 첫번째 그룹

        non_exclusive[i] = new QCheckBox(str2[i], this);
        non_exclusive[i]->setGeometry(xpos + 120, ypos, 100, 30);
        chk_group[1]->addButton(non_exclusive[i], i);  // 두번째 그룹

        ypos += 40;
    }

    label = new QLabel(this);
}

Widget::~Widget()
{

}

void Widget::chkChanged(int id)
{
    QButtonGroup* buttonGroup = (QButtonGroup*)sender();
    QCheckBox* button = (QCheckBox*)buttonGroup->button(id);
    qDebug("CheckBox %d is slected(%s)", id+1, (button->isChecked())?"ON":"OFF");
}

void Widget::chkChanged_Non(int id)
{
    //QButtonGroup* buttonGroup = (QButtonGroup*)sender();
    //QCheckBox* button = (QCheckBox*)buttonGroup->button(id);
    QButtonGroup * buttonGroup = static_cast<QButtonGroup*>(sender());
    QCheckBox * button = static_cast<QCheckBox*>(buttonGroup->button(id));
    qDebug("NonGroup - CheckBox %d is slected(%s)", id+1, (button->isChecked())?"ON":"OFF");

    label->setNum(id+1);
}
