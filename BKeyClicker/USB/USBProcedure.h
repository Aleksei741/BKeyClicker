#pragma once
#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <QVector>
#include <windows.h>

class USBProcedure : public QRunnable 
{
public:
    USBProcedure();
    ~USBProcedure();

    void run() override;

    bool initialize();
    bool EnumUsbDevice();
    std::vector<std::wstring> getDevicePaths(); 
    bool openDevice(const std::wstring& devicePath);
    void closeDevice();

    bool readData(unsigned char* buffer, DWORD bufferSize, DWORD& bytesRead);
    bool writeData(unsigned char* buffer, DWORD bufferSize);

    unsigned short getVendorID();
    unsigned short getProductID();
    unsigned short getInputReportByteLength();
    unsigned short getOutputReportByteLength();

private:
    HDEVINFO hDevInfo; //информация о списке устройств
    SP_DEVINFO_DATA dInf; //массив данных об устройстве
    SP_DEVICE_INTERFACE_DATA dIntDat; //массив данных об интерфейсе
    PSP_DEVICE_INTERFACE_DETAIL_DATA dIntDet = nullptr;
    GUID hidGuid;

    QString devicePath_;

    const std::string _vid = "vid_10c4";
    const std::string _pid = "pid_82cd";

    bool getDeviceCapabilities(const std::wstring& devicePath);
};


class ConnectionMonitor : public QRunnable 
{
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