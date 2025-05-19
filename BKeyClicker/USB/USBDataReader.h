#pragma once
#include <atomic>

#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

#include <windows.h>


class USBDataReader : public QRunnable
{
public:
    USBDataReader(HANDLE fileID, int len_package, QWaitCondition* dataReady);
    ~USBDataReader() override;

    void run() override;
    

private:
    HANDLE fileID_;
    int len_package_;
    QMutex* mutex_;
    QWaitCondition* dataReady_;
    QByteArray dataBuffer; 
    OVERLAPPED oRead = { 0 };
    std::atomic<bool> stopFlag_;

    void processData(const BYTE* data, DWORD size);
};