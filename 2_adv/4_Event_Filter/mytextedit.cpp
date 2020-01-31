#include "mytextedit.h"

#include <QTextEdit>

#include <QKeyEvent>

myTextEdit::myTextEdit(QWidget *parent) : QTextEdit(parent)
{
    installEventFilter(this);
}


void myTextEdit::keyPressEvent(QKeyEvent *e)
{
    qDebug("keyPressEvent(%x)", e->key());
    switch(e->key())
    {
        case Qt::Key_1:
            qDebug("pushed Key 1");
            return;
            break;
    }
    return QTextEdit::keyPressEvent(e);
}
