#pragma once
#include <atomic>

#include <QCoreApplication>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

#include <windows.h>


class USBDataReader : public QObject
{
public:
    USBDataReader(HANDLE* hDev_);
    ~USBDataReader() override;

signals:
    void DataReceived(QByteArray data);

slots:
    void process();
    void stop();

private:

    HANDLE* hDev;
    OVERLAPPED oRead = { 0 };
    std::atomic<bool> active = true;

    void processData(const BYTE* data, DWORD size);
};