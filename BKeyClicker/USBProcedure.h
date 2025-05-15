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
    HDEVINFO hDevInfoSet;
    SP_DEVINFO_DATA devInfoData;
    SP_DEVICE_INTERFACE_DATA devIfcData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA devIfcDetailData;
    HANDLE hHidDeviceObject;

    GUID hidGuid;

    std::string _vid = "vid_10c4";
    std::string _pid = "pid_82cd";

    bool getDeviceCapabilities(const std::wstring& devicePath);
};

