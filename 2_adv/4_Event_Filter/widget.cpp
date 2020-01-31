#include "widget.h"

#include <QLabel>

#include "mytextedit.h"

#include <QTextEdit>
#include <QEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(100,250);
    label = new QLabel(this);
    label->setText("Power ON");
    label->resize(100,30);

    // 입력제한
    myTextEdit *customwidget = new myTextEdit(this);
    customwidget->resize(100,100);
    customwidget->move(0,40);



    // 입력제한 event-filter
    edit = new QTextEdit(this);
    edit->resize(100,100);
    edit->move(0,150);
    edit->installEventFilter(this);
}

Widget::~Widget()
{

}

void Widget::moveEvent(QMoveEvent*)
{
    label->setText(QString("X:%1, Y:%2").arg(pos().x()).arg(pos().y()));
}


bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if(target == edit)
    {
        qDebug("in eventFilter edit");
        if(event->type() == QEvent::KeyPress)
        {
            if((static_cast<QKeyEvent*>(event))->key() == Qt::Key_1)
            {
                qDebug("pushed Key 1");
                return true;
            }
        }
    }
    return QWidget::eventFilter(target, event);
}



