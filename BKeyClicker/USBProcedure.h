#pragma once

#include <windows.h>
#include <setupapi.h>
#include <hidsdi.h>

#include <string>
#include <vector>

class HIDManager {
public:
    HIDManager();
    ~HIDManager();

    bool initialize();
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
    GUID hidGuid;
    HDEVINFO m_deviceInfoSet;
    HANDLE m_deviceHandle;
    HIDD_ATTRIBUTES m_attributes;
    HIDP_CAPS m_capabilities;
    PHIDP_PREPARSED_DATA m_preparsedData;

    bool getDeviceCapabilities(const std::wstring& devicePath);
};

