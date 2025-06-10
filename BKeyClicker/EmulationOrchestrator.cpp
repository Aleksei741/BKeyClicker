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
EmulationOrchestrator::EmulationOrchestrator(QVector<cTimerButton>& TimerButton, 
    QVector<cConditionButton>& CondotoinButton) 
    : active(true), vTimerButton(TimerButton), vCondotoinButton(CondotoinButton)
{
    
}
//------------------------------------------------------------------------------
EmulationOrchestrator::~EmulationOrchestrator()
{
    
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
void EmulationOrchestrator::UpdateParametersButtonTimer(const MainWindowSignal_DType signal, 
    const QVariant& value, int index)
{ 
    QMutexLocker lk(&mutexProcess);
    switch (signal)
    {
    case MainWindowSignal_DType::Active:
        vTimerButton[index].setActive(value.toBool());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Active, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Window:
        vTimerButton[index].setNWindow(static_cast<nWindows_DType>(value.toInt()));
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters n_Window, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Button:
        vTimerButton[index].setIndexButton(static_cast<Buttons_DType>(value.toInt()));
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters IndexButton, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Period:
        vTimerButton[index].setPeriod(value.toInt());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Period, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Repeate:
        vTimerButton[index].setRepeat(value.toInt());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Repeat, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Pause:
        vTimerButton[index].setPause(value.toInt());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Pause, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Shift:
        vTimerButton[index].setShift(value.toBool());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Shift, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Ctrl:
        vTimerButton[index].setCtrl(value.toBool());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Ctrl, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Alt:
        vTimerButton[index].setAlt(value.toBool());
        emit SaveParametersButtonTimer(index, signal, value);
        qDebug() << "EmulationOrchestrator Update TimerButton parameters Alt, button " << index << ", value " << value;
        break;
    }
}
//------------------------------------------------------------------------------
void EmulationOrchestrator::UpdateParametersButtonCondition(const MainWindowSignal_DType signal, 
    const QVariant& value, int index)
{ 
    QMutexLocker lk(&mutexProcess);
    switch (signal)
    {
    case MainWindowSignal_DType::Active:
        vCondotoinButton[index].setActive(value.toBool());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Active, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Window:
        vCondotoinButton[index].setNWindow(static_cast<nWindows_DType>(value.toInt()));
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters n_Window, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Button:
        vCondotoinButton[index].setIndexButton(static_cast<Buttons_DType>(value.toInt()));
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters IndexButton, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Period:
        vCondotoinButton[index].setPeriod(value.toInt());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Period, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Repeate:
        vCondotoinButton[index].setRepeat(value.toInt());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Repeat, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Pause:
        vCondotoinButton[index].setPause(value.toInt());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Pause, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Shift:
        vCondotoinButton[index].setShift(value.toBool());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Shift, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Ctrl:
        vCondotoinButton[index].setCtrl(value.toBool());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Ctrl, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Alt:
        vCondotoinButton[index].setAlt(value.toBool());
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Alt, button " << index << ", value " << value;
        break;

    case MainWindowSignal_DType::Conditional:
        vCondotoinButton[index].setCondition(static_cast<Condition_DType>(value.toInt()));
        emit SaveParametersButtonCondition(index, signal, value);
        qDebug() << "EmulationOrchestrator Update ButtonCondition parameters Conditional, button " << index << ", value " << value;
        break;
    }
}
//------------------------------------------------------------------------------
