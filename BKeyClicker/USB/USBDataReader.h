#pragma once
#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <windows.h>

class USBDataReader : public QRunnable
{
public:
    USBDataReader(HANDLE fileID, int len_package, QMutex* mutex, QWaitCondition* dataReady);
    ~USBDataReader() override;
    void run() override;

    USBDataReader(const USBDataReader& c) = delete;
    USBDataReader& operator= (const USBDataReader& c) = delete;

private:
    HANDLE fileID_;
    int len_package_;
    QMutex* mutex_;
    QWaitCondition* dataReady_;
    QByteArray dataBuffer; // Shared data buffer (protected by mutex)
    OVERLAPPED oRead = { 0 };
};