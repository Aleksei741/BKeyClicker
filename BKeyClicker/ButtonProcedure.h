#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>

#include <atomic>

class ButtonProcedure : public QObject 
{
    Q_OBJECT

public:
    ButtonProcedure();
    ~ButtonProcedure();

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
};

