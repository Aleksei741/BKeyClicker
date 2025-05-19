#pragma once
#include <QCoreApplication>
#include <QMutex>
#include <QWaitCondition>
#include <QVector>
#include <QDebug>

#include <atomic>
#include <options>

#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <hidsdi.h>

#include "USBDataWriter.h"

class USBProcedure : public QObject
{
public:
    USBProcedure();
    ~USBProcedure();

    bool initialize();
    bool SearchUsbDevice();
    bool isTargetDevice(const QString& hidPath);
    bool openDevice(const QString& devicePath);
    void closeDevice(HANDLE& hDev_);

    QByteArray readData();
    bool writeData(QByteArray& data);

slots:
    void process();
    void stop();

    void handleWriteError();
    void handleRecive(QByteArray data);

signals:
    void GUISetStatusConection(bool status);

private:
    HDEVINFO hDevInfo;  // Дескриптор набора устройств
    SP_DEVINFO_DATA dInf;   // Структура, содержащая информацию об устройстве (SP_DEVINFO_DATA).
    SP_DEVICE_INTERFACE_DATA dIntDat;   // Структура, описывающая интерфейс устройства
    PSP_DEVICE_INTERFACE_DETAIL_DATA dIntDet = nullptr; // Указатель на структуру с детальной информацией об интерфейсе устройства.
    GUID hidGuid;   // GUID (Globally Unique Identifier) для HID-устройств.
    QString DevicePath;    // Строка, хранящая путь к HID-устройству в формате QString.
    HANDLE hDev = nullptr;    //Дескриптор устройсвтва

    const QString _vid = "vid_10c4";
    const QString _pid = "pid_82cd";    

    std::atomic<bool> StatusConection = false;
    std::atomic<bool> active = true;

    //Write
    QThread* threadWrite;
    USBDataWriter* writer;

    //Reade
    QThread* threadReade;
    USBDataWriter* reader;
    QMutex mutexReade;
    QByteArray ReadeData;
};
