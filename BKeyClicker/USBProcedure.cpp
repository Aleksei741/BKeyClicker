#include "USBProcedure.h"
#include <iostream>

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")

HIDManager::HIDManager() :
    m_deviceInfoSet(INVALID_HANDLE_VALUE),
    m_deviceHandle(INVALID_HANDLE_VALUE),
    m_preparsedData(nullptr) 
{
    m_attributes.Size = sizeof(HIDD_ATTRIBUTES);
}

HIDManager::~HIDManager() 
{
    closeDevice();

    if (m_deviceInfoSet != INVALID_HANDLE_VALUE) 
    {
        SetupDiDestroyDeviceInfoList(m_deviceInfoSet);
    }
}

bool HIDManager::initialize() 
{
    
    HidD_GetHidGuid(&hidGuid);

    printf("HidGuid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}\n",
        hidGuid.Data1, hidGuid.Data2, hidGuid.Data3,
        hidGuid.Data4[0], hidGuid.Data4[1], hidGuid.Data4[2], hidGuid.Data4[3],
        hidGuid.Data4[4], hidGuid.Data4[5], hidGuid.Data4[6], hidGuid.Data4[7]);

    // Retrieve a list of all present USB devices with a device interface.
    m_deviceInfoSet = SetupDiGetClassDevs(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (m_deviceInfoSet == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "SetupDiGetClassDevs failed" << std::endl;
        return false;
    }

    return true;
}

std::vector<std::wstring> HIDManager::getDevicePaths() 
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

bool HIDManager::openDevice(const std::wstring& devicePath) 
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

void HIDManager::closeDevice() 
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

bool HIDManager::readData(unsigned char* buffer, DWORD bufferSize, DWORD& bytesRead) 
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

bool HIDManager::writeData(unsigned char* buffer, DWORD bufferSize) 
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

unsigned short HIDManager::getVendorID() 
{
    return m_attributes.VendorID;
}

unsigned short HIDManager::getProductID()
{
    return m_attributes.ProductID;
}

unsigned short HIDManager::getInputReportByteLength()
{
    return m_capabilities.InputReportByteLength;
}

unsigned short HIDManager::getOutputReportByteLength() 
{
    return m_capabilities.OutputReportByteLength;
}

bool HIDManager::getDeviceCapabilities(const std::wstring& devicePath) 
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