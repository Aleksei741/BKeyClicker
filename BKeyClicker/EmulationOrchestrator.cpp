//******************************************************************************
//include
//******************************************************************************
#include "EmulationOrchestrator.h"
//******************************************************************************
// Variables
//******************************************************************************
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------


//******************************************************************************
// Class function
//******************************************************************************
EmulationOrchestrator::EmulationOrchestrator() : active(true)
{
    
}
//------------------------------------------------------------------------------
EmulationOrchestrator::~EmulationOrchestrator()
{
    
}
//------------------------------------------------------------------------------
void EmulationOrchestrator::process()
{
    qint32 pause;

    qDebug() << "EmulationOrchestrator process start: " << QThread::currentThreadId();

    while (active)
    {
        mutexPause.lock();
        while (paused)
        {
            qDebug() << "EmulationOrchestrator process pause";
            cvWait.wait(&mutexPause);
            qDebug() << "EmulationOrchestrator process begine";
        }
        mutexPause.unlock();

        pause = EmulationMachine();
        
        QThread::msleep(pause);
    }

    qDebug() << "EmulationOrchestrator process stop.";
    emit finished();
}
//------------------------------------------------------------------------------
void EmulationOrchestrator::stop() 
{
    mutexPause.lock();
    active = false;
    cvWait.wakeAll();
    mutexPause.unlock();
}
//------------------------------------------------------------------------------
void EmulationOrchestrator::pause() 
{
    QMutexLocker locker(&mutexPause);
    paused = true;
}
//------------------------------------------------------------------------------
void EmulationOrchestrator::resume() 
{
    QMutexLocker locker(&mutexPause);
    paused = false;
    cvWait.wakeAll();
}
//------------------------------------------------------------------------------
qint32 EmulationOrchestrator::EmulationMachine(void)
{
    qint32 pause = 1;



    return pause;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
