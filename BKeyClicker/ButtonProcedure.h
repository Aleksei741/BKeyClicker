#pragma once
#include <QApplication>

class ButtonProcedure : public QObject 
{
    Q_OBJECT

public:
    ButtonProcedure();
    ~ButtonProcedure();

public slots:
    void process();

signals:
    void finished();
    void stop();
    void pause();
    void resume();
    void error(QString err);

private:
    bool m_running;
    bool m_paused;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
};


/*QThread* thread = new QThread;
Worker* worker = new Worker();
worker->moveToThread(thread);
connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
connect(thread, SIGNAL(started()), worker, SLOT(process()));
connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
thread->start();*/