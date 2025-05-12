#include "ButtonProcedure.h"


ButtonProcedure::ButtonProcedure()
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
            qDebug() << "Поток приостановлен.";
            m_waitCondition.wait(&m_mutex); // Освобождает мьютекс и ждет сигнала
            qDebug() << "Поток возобновлен.";
        }
        m_mutex.unlock();

        // ... Выполняем какую-то работу ...
        qDebug() << "Working...";
        QThread::msleep(10);
    }

    qDebug() << "Worker::process() завершен.";
    emit finished();
}

void ButtonProcedure::stop() {
    m_mutex.lock();
    m_running = false;
    m_waitCondition.wakeAll(); // Разбудить поток, если он ждет
    m_mutex.unlock();
}

void ButtonProcedure::pause() {
    QMutexLocker locker(&m_mutex); // Автоматически блокирует мьютекс
    m_paused = true;
}

void ButtonProcedure::resume() {
    QMutexLocker locker(&m_mutex); // Автоматически блокирует мьютекс
    m_paused = false;
    m_waitCondition.wakeAll(); // Разбудить поток
}