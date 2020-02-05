#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "thread.h"

#include <QThreadPool>
#include <QRunnable>
#include <QDebug>

class RunnableTask : public QRunnable
{
    void run()
    {
        qDebug() << "Runnable Thread" << QThread::currentThreadId();
    }

};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Thread* th;
};
#endif // WIDGET_H
