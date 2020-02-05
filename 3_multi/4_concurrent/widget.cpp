#include "widget.h"

#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>
#include <QThread>
#include <QDebug>

#include <QProgressDialog>

const int iter = 50;

static void spin(int &iter)
{
    const int work = 1000 * 1000 * 40;
    volatile int v = 0;
    for (int j = 0; j < work; j++)
    {
        ++v;
    }
    qDebug() << "iter" << iter << "in thread" << QThread::currentThreadId() << QThread::currentThread();

}

static void display(const QString &msg)
{
    qDebug() << __func__ << QThread::currentThreadId() << msg;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(3);

    qDebug() << "Widget Thread" << QThread::currentThreadId();

    QVector<int> vector;
    for(int i = 0; i<iter; ++i)
    {
        vector.append(i);
    }

    QProgressDialog dialog;
    dialog.setLabelText(QString("core %1").arg(QThread::idealThreadCount()));

    QFutureWatcher<void> watcher;

    connect(&watcher, SIGNAL(finished()), &dialog, SLOT(reset()));
    connect(&watcher, SIGNAL(progressRangeChanged(int, int)), &dialog, SLOT(setRange(int, int)));
    connect(&watcher, SIGNAL(progressValueChanged(int)), &dialog, SLOT(setValue(int)));
    connect(&dialog, SIGNAL(canceled()), &watcher, SLOT(cancel()));

    watcher.setFuture(QtConcurrent::map(vector, spin));
    dialog.exec();

    QFuture<void> future1 = QtConcurrent::run(display, QObject::tr("HI Concurrent"));
    watcher.setFuture(future1);

    watcher.waitForFinished();

    qDebug() << "Canceled?" << watcher.future().isCanceled();
}

Widget::~Widget()
{
}

