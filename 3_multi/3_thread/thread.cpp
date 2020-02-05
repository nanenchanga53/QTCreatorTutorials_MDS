#include "thread.h"

Thread::Thread(QObject* obj)
{
    label = (QLabel*)obj;
    stopFlag = Play;
}

void Thread::run()
{
    for(int count = 0;;) // while(true)
    {
        mutex.lock();
        if(stopFlag == Stop)
        {
            waitcond.wait(&mutex);
        }

        mutex.unlock();
        emit setLabeled(QString("run %1").arg(count++));
        sleep(1);
    }
}

void Thread::stopThread()
{
    stopFlag = Stop;
}

void Thread::resumeThread()
{
    mutex.lock();
    stopFlag = Play;
    waitcond.wakeAll();
    mutex.unlock();
}
