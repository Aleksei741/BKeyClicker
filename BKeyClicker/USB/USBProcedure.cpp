#include "USBProcedure.h"
#include <iostream>

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")

USBProcedure::USBProcedure()
{
    setAutoDelete(true);

    initialize();

    //
    threadWrite = new QThread;
    writer = new USBDataWriter(&hDev);
    QObject::connect(writer, &USBDataWriter::writeError, this, handleWriteError);
    writer->moveToThread(threadWrite);
    QObject::connect(threadWrite, &QThread::started, writer, &USBDataWriter::process);
    QObject::connect(writer, &USBDataWriter::finished, threadWrite, &QThread::quit);
    QObject::connect(writer, &USBDataWriter::finished, writer, &USBDataWriter::deleteLater);
    QObject::connect(threadWrite, &QThread::finished, threadWrite, &QThread::deleteLater);
    threadWrite->start();

    threadReade = new QThread;
    reader = new USBDataWriter(&hDev);
    reader->moveToThread(threadReade);
    QObject::connect(threadReade, &QThread::started, reader, &USBDataReader::process);
    QObject::connect(reader, &USBDataReader::finished, threadReade, &QThread::quit);
    QObject::connect(reader, &USBDataReader::finished, reader, &USBDataReader::deleteLater);
    QObject::connect(threadReade, &QThread::finished, threadReade, &QThread::deleteLater);
    threadReade->start();
}
//------------------------------------------------------------------------------
USBProcedure::~USBProcedure() 
{
    writer->stop();
    threadWrite->quit();
    threadWrite->wait();

    reader->stop();
    threadReade->quit();
    threadReade->wait();

    closeDevice();
}
//------------------------------------------------------------------------------

bool USBProcedure::initialize() 
{    
    HidD_GetHidGuid(&hidGuid);

    qDebug() << "USBProcedure HidGuid: " << hidGuid.Data1 << " " << hidGuid.Data2 << " " << hidGuid.Data3 << " "
        << hidGuid.Data4[0] << " " << hidGuid.Data4[1] << " " << hidGuid.Data4[2] << " " << hidGuid.Data4[3] << " "
        << hidGuid.Data4[4] << " " << hidGuid.Data4[5] << " " << hidGuid.Data4[6] << " " << hidGuid.Data4[7];

    return true;
}
//------------------------------------------------------------------------------
std::options<QString> USBProcedure::SearchUsbDevice()
{
    std::options<QString> status = std::nullopt;
    unsigned long rLength = 0;
    quint16 i = 0;
    QString& devicePath_;

    hDevInfo = SetupDiGetClassDevs(&hidGuid, nullptr, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (hDevInfo != INVALID_HANDLE_VALUE)
    {
        dInf.cbSize = sizeof(SP_DEVINFO_DATA);
        dIntDat.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        
        while (SetupDiEnumDeviceInterfaces(hDevInfo, 0, &hidGuid, i, &dIntDat))
        {
            SetupDiGetDeviceInterfaceDetail(hDevInfo, &dIntDat, 0, 0, &rLength, 0);
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) 
            {
                qDebug() << "USBProcedure Handle error";
                break;
            }

            dIntDet = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(malloc(rLength));
            dIntDet->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &dIntDat, dIntDet, rLength, &rLength, 0))
            {
                qDebug() << "USBProcedure Handle error 2";
                free(dIntDet);
                break;
            }

            DevicePath_ = QString::fromWCharArray(dIntDet->DevicePath, wcslen(dIntDet->DevicePath));
            free(dIntDet);

            qDebug() << "USBProcedure devicePath: " << DevicePath_;

            if (isTargetDevice(DevicePath_))
            {
                qDebug() << "USBProcedure search finish";
                status = DevicePath_;
                break;
            }
            i++;
        }
        SetupDiDestroyDeviceInfoList(hDevInfo);
    }

    return status;
}
//------------------------------------------------------------------------------
bool USBProcedure::isTargetDevice(const QString& hidPath)
{
    if (hidPath.contains(_vid))
        if (hidPath.contains(_pid))
            return true;

    return false;
}
//------------------------------------------------------------------------------
bool USBProcedure::openDevice(const QString& devicePath)
{
    std::wstring wPath = devicePath.toStdWString();

    hDev = CreateFile(
        wPath.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hDev != INVALID_HANDLE_VALUE)
    {
        StatusConection = true;
    }
    else
    {
        qDebug() << "USBProcedure CreateFile INVALID_HANDLE_VALUE";
    }

    return getDeviceCapabilities(devicePath);
}
//------------------------------------------------------------------------------
void USBProcedure::closeDevice(HANDLE& hDev_)
{
    if(hDev_ && hDev_ != INVALID_HANDLE_VALUE)
        CloseHandle(hDev_);
    hDev_ = nullptr;
}
//------------------------------------------------------------------------------
QByteArray USBProcedure::readData()
{
    QMutexLocker(mutexReade);
    return ReadeData;
}
//------------------------------------------------------------------------------
bool USBProcedure::writeData(QByteArray& data)
{
    bool ret;
    ret = writer->write(data);
    return ret;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
void USBProcedure::process()
{
    while (active)
    {
        if (!StatusConection)
        {
            closeDevice(hDev);
            DevicePath = SearchUsbDevice();
            if (DevicePath)
            {
                openDevice(DevicePath);
            }
        }

        emit GUISetStatusConection(static_cast<bool>(StatusConection));

        QThread::sleep(std::chrono::milliseconds{ 1000 });
    }
}
//------------------------------------------------------------------------------
void USBProcedure::stop()
{
    active = false;
}
//------------------------------------------------------------------------------
void  USBProcedure::handleWriteError()
{
    StatusConection = false;
    emit GUISetStatusConection(static_cast<bool>(StatusConection));
}
//------------------------------------------------------------------------------
void  USBProcedure::handleRecive(QByteArray data)
{
    QMutexLocker(mutexReade);
    ReadeData = data;
}
//------------------------------------------------------------------------------


/*unsigned short USBProcedure::getVendorID() 
{
    return m_attributes.VendorID;
}

unsigned short USBProcedure::getProductID()
{
    return m_attributes.ProductID;
}

unsigned short USBProcedure::getInputReportByteLength()
{
    return m_capabilities.InputReportByteLength;
}

unsigned short USBProcedure::getOutputReportByteLength() 
{
    return m_capabilities.OutputReportByteLength;
}

bool USBProcedure::getDeviceCapabilities(const std::wstring& devicePath)
{
    if (!HidD_GetAttributes(m_deviceHandle, &m_attributes)) 
    {
        std::cerr << "HidD_GetAttributes failed" << std::endl;
        return false;
    }

    if (!HidD_GetPreparsedData(m_deviceHandle, &m_preparsedData)) 
    {
        std::cerr << "HidD_GetPreparsedData failed" << std::endl;
        return false;
    }

    NTSTATUS status = HidP_GetCaps(m_preparsedData, &m_capabilities);
    if (status != HIDP_STATUS_SUCCESS) 
    {
        std::cerr << "HidP_GetCaps failed" << std::endl;
        return false;
    }

    return true;
}*/