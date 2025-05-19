#pragma once
#include <atomic>

#include <QCoreApplication>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QObject>

#include <windows.h>


class USBDataReader : public QObject
{
    Q_OBJECT

public:
    USBDataReader(HANDLE* hDev_);
    ~USBDataReader();

signals:
    void readUSBError();
    void finished();
    void DataReceived(QByteArray data);    

public slots:
    void process();
    void stop();

private:

    HANDLE* hDev;
    OVERLAPPED oRead = { 0 };
    std::atomic<bool> active = true;

    void processData(const BYTE* data, DWORD size);
};