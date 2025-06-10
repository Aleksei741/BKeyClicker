#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>
#include <QDebug>
#include <QMutexLocker>

#include <atomic>

#include "Definitions.h"
#include "cConditionButton.h"
#include "cTimerButton.h"

class EmulationOrchestrator : public QObject 
{
    Q_OBJECT

public:
    EmulationOrchestrator(QVector<cTimerButton>& TimerButton, QVector<cConditionButton>& CondotoinButton);
    ~EmulationOrchestrator();

public slots:
    void process();
    void stop();
    void pause();
    void resume();
    //-----------
    void UpdateParametersButtonTimer(const MainWindowSignal_DType signal, const QVariant& value, int index);
    void UpdateParametersButtonCondition(const MainWindowSignal_DType signal, const QVariant& value, int index);

signals:
    void finished();
    //-----------
    void SaveParametersButtonTimer(qint32 num, MainWindowSignal_DType SignalType, const QVariant& value);
    void SaveParametersButtonCondition(qint32 num, MainWindowSignal_DType SignalType, const QVariant& value);

private:
    std::atomic<bool> active;
    std::atomic<bool> paused;
    QMutex mutexPause;
    QWaitCondition cvWait;

    QMutex mutexProcess;

    QVector<cTimerButton>& vTimerButton;
    QVector<cConditionButton>& vCondotoinButton;

    qint32 EmulationMachine(void);
};

