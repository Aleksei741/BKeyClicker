#include "ButtonProcedure.h"


ButtonProcedure::ButtonProcedure() : m_running(true), m_paused(false)
{
    
}

ButtonProcedure::~ButtonProcedure()
{
    
}

void ButtonProcedure::process()
{
    qDebug() << "ButtonProcedure start process: " << QThread::currentThreadId();

    while (m_running) 
    {
        m_mutex.lock();
        while (m_paused) 
        {
            qDebug() << "ButtonProcedure ";
            m_waitCondition.wait(&m_mutex);
            qDebug() << "����� �����������.";
        }
        m_mutex.unlock();

        qDebug() << "Working...";
        QThread::msleep(10);
    }

    qDebug() << "Worker::process() ��������.";
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