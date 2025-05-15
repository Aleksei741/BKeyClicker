#pragma once
#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <windows.h>

class USBDataWriter : public QRunnable
{
public:
    USBDataWriter(HANDLE fileID, QMutex* mutex, QWaitCondition* dataReady)
        : fileID_(fileID), mutex_(mutex), dataReady_(dataReady) {}

    void run() override
    {
        while (true) {
            mutex_->lock();
            dataReady_->wait(mutex_);  // Wait for data to be available
            QByteArray data = dataToWrite;  // Get data to write
            mutex_->unlock();

            if (data.isEmpty()) break;  // Check for stop condition

            DWORD bytesWritten;
            BOOL success = WriteFile(fileID_, data.data(), data.size(), &bytesWritten, NULL);
            if (!success) {
                qDebug() << "WriteFile failed:" << GetLastError();
                break;
            }
        }
    }
private:
    HANDLE fileID_;
    QMutex* mutex_;
    QWaitCondition* dataReady_;
    QByteArray dataToWrite;
};

class ConnectionMonitor : public QRunnable {
public:
    ConnectionMonitor(HANDLE& fileID, std::wstring devicePath, std::function<void(HANDLE)> onConnected)
        : fileID_(fileID), devicePath_(devicePath), onConnected_(onConnected) {}

    void run() override {
        while (true) {
            if (fileID_ == INVALID_HANDLE_VALUE) {
                // Attempt to reconnect
                HANDLE newFileID = CreateFile(devicePath_.c_str(),
                    GENERIC_READ | GENERIC_WRITE,
                    0,
                    NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_OVERLAPPED,
                    NULL);

                if (newFileID != INVALID_HANDLE_VALUE) {
                    QMutex mutex;
                    QMutexLocker locker(&mutex);
                    fileID_ = newFileID;
                    onConnected_(fileID_);  // Callback function to signal successful connection
                    qDebug() << "Reconnected to device.";
                }
                else {
                    qDebug() << "Failed to reconnect:" << GetLastError();
                }
            }

            QThread::sleep(5); // Check every 5 seconds
        }
    }

private:
    HANDLE& fileID_;
    std::wstring devicePath_;
    std::function<void(HANDLE)> onConnected_;
};