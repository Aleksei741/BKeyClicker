#pragma once
#include <QCoreApplication>
#include <QMutex>
#include <QWaitCondition>

#include <atomic>

#include <windows.h>

class USBDataWriter : public QObject
{
public:
    USBDataWriter(HANDLE* hDev_);
    ~USBDataWriter();
    bool write(QByteArray data);

signals:
    void writeError();

slots:
    void process();
    void stop();

private:
    HANDLE *hDev;
    QMutex mutexWrite;
    QWaitCondition* cvWrite;
    QQueue<QByteArray> dataToWrite;

    OVERLAPPED oWrite = { 0 };

    std::atomic<bool> active = true;

    void process() override;
};

