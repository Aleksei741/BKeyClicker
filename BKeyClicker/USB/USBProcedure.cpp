#include "USBProcedure.h"
#include <iostream>

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")

USBProcedure::USBProcedure()
{
    
}

USBProcedure::~USBProcedure() 
{

}

bool USBProcedure::initialize() 
{    
    HidD_GetHidGuid(&hidGuid);

    qDebug() << "USBProcedure HidGuid: " << hidGuid.Data1 << " " << hidGuid.Data2 << " " << hidGuid.Data3 << " "
        << hidGuid.Data4[0] << " " << hidGuid.Data4[1] << " " << hidGuid.Data4[2] << " " << hidGuid.Data4[3] << " "
        << hidGuid.Data4[4] << " " << hidGuid.Data4[5] << " " << hidGuid.Data4[6] << " " << hidGuid.Data4[7];

    return true;
}

bool USBProcedure::EnumUsbDevice()
{
    bool status = false;
    quint16 rLength = 0;
    quint16 i = 0;

    hDevInfo = SetupDiGetClassDevs(&hidGuid, NULL, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

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

            QVector<quint8> buffer(rLength);
            dIntDet = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA*>(buffer.data());
            dIntDet->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &dIntDat, dIntDet, rLength, &rLength, 0))
            {
                qDebug() << "USBProcedure Handle error 2";
                break;
            }

            devicePath_ = QString::fromWCharArray(dIntDet->DevicePath, wcslen(dIntDet->DevicePath));

            if (!flg)
            {
                if (connecthid(devpath)) //пробуем соединиться.
                {
                    status = TRUE; //если успешно
                    break;
                }
            }
            i++;
        }
        SetupDiDestroyDeviceInfoList(hDevInfo);
    }

    return status;
}

std::vector<std::wstring> USBProcedure::getDevicePaths() 
{
    std::vector<std::wstring> devicePaths;
    SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
    deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    if (m_deviceInfoSet == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "Device info set is not initialized" << std::endl;
        return devicePaths; // Return empty vector
    }

    for (DWORD i = 0; SetupDiEnumDeviceInterfaces(m_deviceInfoSet, NULL, &hidGuid, i, &deviceInterfaceData); ++i)
    {
        DWORD requiredSize = 0;
        SetupDiGetDeviceInterfaceDetail(m_deviceInfoSet, &deviceInterfaceData, NULL, 0, &requiredSize, NULL);

        PSP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
        if (!deviceInterfaceDetailData) {
            std::cerr << "Failed to allocate memory for device interface detail data" << std::endl;
            continue; // Skip this device
        }
        deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if (!SetupDiGetDeviceInterfaceDetail(m_deviceInfoSet, &deviceInterfaceData, deviceInterfaceDetailData, requiredSize, NULL, NULL))
        {
            std::cerr << "SetupDiGetDeviceInterfaceDetail failed" << std::endl;
            free(deviceInterfaceDetailData);
            continue; // Skip this device
        }

        devicePaths.push_back(deviceInterfaceDetailData->DevicePath);
        free(deviceInterfaceDetailData);
    }

    return devicePaths;
}

bool USBProcedure::openDevice(const std::wstring& devicePath) 
{
    m_deviceHandle = CreateFileW(
        devicePath.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (m_deviceHandle == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "CreateFile failed" << std::endl;
        return false;
    }

    return getDeviceCapabilities(devicePath);
}

void USBProcedure::closeDevice() 
{
    if (m_deviceHandle != INVALID_HANDLE_VALUE) 
    {
        CloseHandle(m_deviceHandle);
        m_deviceHandle = INVALID_HANDLE_VALUE;
    }

    if (m_preparsedData) 
    {
        HidD_FreePreparsedData(m_preparsedData);
        m_preparsedData = nullptr;
    }
}

bool USBProcedure::readData(unsigned char* buffer, DWORD bufferSize, DWORD& bytesRead) 
{
    if (m_deviceHandle == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "Device not open" << std::endl;
        return false;
    }

    if (!ReadFile(m_deviceHandle, buffer, bufferSize, &bytesRead, NULL)) 
    {
        std::cerr << "ReadFile failed" << std::endl;
        return false;
    }

    return true;
}

bool USBProcedure::writeData(unsigned char* buffer, DWORD bufferSize) 
{
    if (m_deviceHandle == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "Device not open" << std::endl;
        return false;
    }

    DWORD bytesWritten;
    if (!WriteFile(m_deviceHandle, buffer, bufferSize, &bytesWritten, NULL)) 
    {
        std::cerr << "WriteFile failed" << std::endl;
        return false;
    }

    return true;
}

unsigned short USBProcedure::getVendorID() 
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
}