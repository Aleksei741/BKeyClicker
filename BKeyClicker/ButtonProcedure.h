#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>

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
    void error(QString err);

private:
    bool m_running;
    bool m_paused;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
};

