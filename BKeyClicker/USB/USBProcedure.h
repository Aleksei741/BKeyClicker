#pragma once
#include <QCoreApplication>
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <QVector>
#include <QDebug>

#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <hidsdi.h>


class USBProcedure : public QRunnable 
{
public:
    USBProcedure();
    ~USBProcedure();

    void run() override;

    bool initialize();
    bool EnumUsbDevice();
    bool isTargetDevice(const QString& hidPath);
    bool openDevice(const QString& devicePath);
    void closeDevice();

    bool readData(unsigned char* buffer, DWORD bufferSize, DWORD& bytesRead);
    bool writeData(unsigned char* buffer, DWORD bufferSize);

private:
    // Дескриптор набора устройств, возвращаемый SetupDiGetClassDevs.
    // Используется для перечисления устройств определенного класса (например, HID).
    HDEVINFO hDevInfo;

    // Структура, содержащая информацию об устройстве (SP_DEVINFO_DATA).
    // Заполняется функцией SetupDiEnumDeviceInfo при перечислении устройств.
    SP_DEVINFO_DATA dInf;

    // Структура, описывающая интерфейс устройства (SP_DEVICE_INTERFACE_DATA).
    // Используется для получения пути к устройству через SetupDiGetDeviceInterfaceDetail.
    SP_DEVICE_INTERFACE_DATA dIntDat;

    // Указатель на структуру с детальной информацией об интерфейсе устройства.
    // Содержит путь к устройству (например, "\\?\hid#vid_1234&pid_5678...").
    // Выделяется динамически и требует освобождения через free().
    PSP_DEVICE_INTERFACE_DETAIL_DATA dIntDet = nullptr;

    // GUID (Globally Unique Identifier) для HID-устройств.
    // Заполняется функцией GetHidGuid, чтобы идентифицировать HID-класс.
    GUID hidGuid;

    // Строка, хранящая путь к HID-устройству в формате QString.
    // Например: "\\\\?\\hid#vid_1234&pid_5678#..."
    QString devicePath_;

    const QString _vid = "vid_10c4";
    const QString _pid = "pid_82cd";

    HANDLE fileID = nullptr;
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