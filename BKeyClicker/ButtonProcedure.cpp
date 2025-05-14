#include "ButtonProcedure.h"


ButtonProcedure::ButtonProcedure() : m_running(true), m_paused(false)
{
    
}

ButtonProcedure::~ButtonProcedure()
{
    
}

void ButtonProcedure::process()
{
    qDebug() << "ButtonProcedure process start: " << QThread::currentThreadId();

    while (m_running) 
    {
        m_mutex.lock();
        while (m_paused) 
        {
            qDebug() << "ButtonProcedure process pause";
            m_waitCondition.wait(&m_mutex);
            qDebug() << "ButtonProcedure process begine";
        }
        m_mutex.unlock();

        qDebug() << "Working...";
        QThread::msleep(10);
    }

    qDebug() << "ButtonProcedure process stop.";
    emit finished();
}

void ButtonProcedure::stop() 
{
    m_mutex.lock();
    m_running = false;
    m_waitCondition.wakeAll();
    m_mutex.unlock();
}

void ButtonProcedure::pause() 
{
    QMutexLocker locker(&m_mutex);
    m_paused = true;
}

void ButtonProcedure::resume() 
{
    QMutexLocker locker(&m_mutex);
    m_paused = false;
    m_waitCondition.wakeAll();
}