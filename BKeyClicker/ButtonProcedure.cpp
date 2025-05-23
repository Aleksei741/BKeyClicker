#include "ButtonProcedure.h"


ButtonProcedure::ButtonProcedure() : active(true), mutexPause(false)
{
    
}

ButtonProcedure::~ButtonProcedure()
{
    
}

void ButtonProcedure::process()
{
    qDebug() << "ButtonProcedure process start: " << QThread::currentThreadId();

    while (active)
    {
        mutexPause.lock();
        while (paused)
        {
            qDebug() << "ButtonProcedure process pause";
            cvWait.wait(&mutexPause);
            qDebug() << "ButtonProcedure process begine";
        }
        mutexPause.unlock();

        QCoreApplication::processEvents();

        qDebug() << "ButtonProcedure Working...";
        QThread::msleep(1);
    }

    qDebug() << "ButtonProcedure process stop.";
    emit finished();
}

void ButtonProcedure::stop() 
{
    mutexPause.lock();
    active = false;
    cvWait.wakeAll();
    mutexPause.unlock();
}

void ButtonProcedure::pause() 
{
    QMutexLocker locker(&mutexPause);
    paused = true;
}

void ButtonProcedure::resume() 
{
    QMutexLocker locker(&mutexPause);
    paused = false;
    cvWait.wakeAll();
}