#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QLabel>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(QObject* obj = nullptr);


public:
    enum {Stop = 0, Play};

private:
    QLabel* label;
    QWaitCondition waitcond;
    QMutex mutex;
    qint32 stopFlag;

protected:
    void run();

signals:
    void setLabeled(QString);

public slots:
    void stopThread();
    void resumeThread();
};

#endif // THREAD_H
