#include "USBDataReader.h"

USBDataReader::USBDataReader(HANDLE* hDev_)
    : hDev(hDev_)
{
    oRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (oRead.hEvent == NULL)
    {
        qDebug() << "USBDataReader CreateEvent failed: " << GetLastError();
        throw std::runtime_error("USBDataReader CreateEvent failed");
    }
}
//------------------------------------------------------------------------------
USBDataReader::~USBDataReader()
{
    CloseHandle(oRead.hEvent);
}
//------------------------------------------------------------------------------
void USBDataReader::processData(const BYTE* data, DWORD size)
{
    QByteArray byteArray(reinterpret_cast<const char*>(data), size);
    emit DataReceived(byteArray);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
void USBDataReader::process()
{
    BYTE reportread[256];
    DWORD bytesRead = 255;

    while (active)
    {
        ResetEvent(oRead.hEvent);

        if (*hDev != INVALID_HANDLE_VALUE)
        {
            if (!ReadFile(*hDev, reportread, bytesRead + 1, NULL, &oRead))
            {
                DWORD error = GetLastError();
                if (error != ERROR_IO_PENDING)
                {
                    qDebug() << "USBDataReader ReadFile failed: " << error << " Handle: " << *hDev;
                    emit readUSBError();
                }

                DWORD waitResult = WaitForSingleObject(oRead.hEvent, 100);

                if (waitResult == WAIT_OBJECT_0)
                {
                    if (!GetOverlappedResult(*hDev, &oRead, &bytesRead, FALSE))
                    {
                        error = GetLastError();
                        qDebug() << "USBDataReader GetOverlappedResult failed: " << error;
                        emit readUSBError();
                    }
                    else
                    {
                        if (bytesRead > 0)
                        {
                            processData(reportread, bytesRead);
                        }
                    }
                }
                else if (waitResult == WAIT_TIMEOUT)
                {
                    CancelIo(*hDev);
                }
            }
            else
            {
                // Синхронное завершение
                bytesRead = oRead.InternalHigh;
                if (bytesRead > 0)
                {
                    processData(reportread, bytesRead);
                }
            }
        }
    }

    CancelIo(*hDev);

    qDebug() << "USBDataReader process stop.";
    emit finished();
}
//------------------------------------------------------------------------------
void USBDataReader::stop()
{
    active = false;
}
//------------------------------------------------------------------------------

