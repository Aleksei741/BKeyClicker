#pragma once
#include <QCoreApplication>
#include <QMutex>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QQueue>
#include <QDebug>
#include <QObject>

#include <atomic>

#include <windows.h>

class USBDataWriter : public QObject
{
    Q_OBJECT

public:
    USBDataWriter(HANDLE* hDev_);
    ~USBDataWriter();
    bool write(QByteArray data);

signals:
    void finished();
    void writeError();

public slots:
    void process();
    void stop();

private:
    HANDLE *hDev;
    QMutex mutexWrite;
    QWaitCondition cvWrite;
    QQueue<QByteArray> dataToWrite;

    OVERLAPPED oWrite = { 0 };

    std::atomic<bool> active = true;
};

