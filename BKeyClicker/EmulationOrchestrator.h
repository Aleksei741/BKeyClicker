#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>

#include <atomic>

class EmulationOrchestrator : public QObject 
{
    Q_OBJECT

public:
    EmulationOrchestrator();
    ~EmulationOrchestrator();

public slots:
    void process();
    void stop();
    void pause();
    void resume();

signals:
    void finished();

private:
    std::atomic<bool> active;
    std::atomic<bool> paused;
    QMutex mutexPause;
    QWaitCondition cvWait;

    qint32 EmulationMachine(void);
};

