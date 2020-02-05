#include "widget.h"

#include <QTextEdit>
#include <QProcess>
#include <QByteArray>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QProcess cmd;
    cmd.start("ls", QStringList() << "-l");
    if (!cmd.waitForStarted()) {
        qDebug() << "Failed";
        return;
    }

    if (!cmd.waitForFinished()) {
        qDebug() << "Failed";
        return;
    }

    QByteArray result = cmd.readAllStandardOutput();
    QTextEdit* edit = new QTextEdit(this);

    edit->setReadOnly(true);
    edit->append(result);
    edit->show();
}

Widget::~Widget()
{
}

