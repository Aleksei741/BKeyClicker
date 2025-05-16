#pragma once
#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <windows.h>

class USBDataWriter : public QRunnable
{
public:
    USBDataWriter(HANDLE fileID, QMutex* mutex, QWaitCondition* dataReady);
    void run() override;
private:
    HANDLE fileID_;
    QMutex* mutex_;
    QWaitCondition* dataReady_;
    QByteArray dataToWrite;
};

