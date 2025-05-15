#include "USBDataReader.h"

USBDataReader::USBDataReader(HANDLE fileID, int len_package, QMutex* mutex, QWaitCondition* dataReady)
    : fileID_(fileID), len_package_(len_package), mutex_(mutex), dataReady_(dataReady)
{
    oRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (oRead.hEvent == NULL)
    {
        qDebug() << "USBDataReader CreateEvent failed: " << GetLastError();
        throw std::invalid_argument("USBDataReader CreateEvent failed");
    }
}

~USBDataReader() override
{
    CloseHandle(oRead.hEvent);
}

void USBDataReader::run() override
{
    BYTE reportread[256]; // Adjust size as needed
    DWORD Bytes;        

    while (true) // Use a mechanism to stop the loop gracefully
    {
        ResetEvent(oRead.hEvent);

        BOOL StatusReadeUSBDevice = ReadFile(fileID_, &reportread[0], len_package_ + 1, &Bytes, &oRead);

        if (StatusReadeUSBDevice)
        {
            QByteArray data((char*)reportread, Bytes);
            {
                QMutexLocker locker(mutex_); // Protect shared data
                dataBuffer = data;         // Copy data to buffer
            }
            dataReady_->wakeOne();  // Signal that data is available
        }
        else
        {
            DWORD error = GetLastError();
            if (error == ERROR_IO_PENDING)
            {
                DWORD waitResult = WaitForSingleObject(oRead.hEvent, INFINITE);
                if (waitResult == WAIT_OBJECT_0)
                {
                    if (GetOverlappedResult(fileID_, &oRead, &Bytes, TRUE))
                    {
                        QByteArray data((char*)reportread, Bytes);
                        {
                            QMutexLocker locker(mutex_);
                            dataBuffer = data;
                        }
                        dataReady_->wakeOne();
                    }
                    else
                    {
                        qDebug() << "USBDataReader GetOverlappedResult failed:" << GetLastError();
                        break;
                    }
                }
                else
                {
                    qDebug() << "USBDataReader WaitForSingleObject failed:" << GetLastError();
                    break;
                }
            }
            else
            {
                qDebug() << "USBDataReader ReadFile failed:" << error;
                break;
            }
        }
    }    
}
