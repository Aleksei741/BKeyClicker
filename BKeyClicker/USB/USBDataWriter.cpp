#include "USBDataWriter.h"

USBDataWriter::USBDataWriter(HANDLE* hDev_)
    : hDev(hDev_)
{
    setAutoDelete(true);

    oWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (oWrite.hEvent == NULL)
    {
        qDebug() << "USBDataWriter CreateEvent failed: " << GetLastError();
        throw std::runtime_error("USBDataWriter CreateEvent failed");
    }
}
//------------------------------------------------------------------------------
USBDataWriter::~USBDataWriter()
{
    CloseHandle(oWrite.hEvent);   
}
//------------------------------------------------------------------------------
bool USBDataWriter::write(QByteArray data)
{
    QMutexLocker(mutexWrite);
    dataToWrite.enqueue(data);
    cvWrite.wakeOne();

    return true;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
void USBDataWriter::process()
{
    QByteArray data;
    DWORD bytesWritten;
    BOOL ret;

    while (active)
    {
        {
            QMutexLocker(mutexWrite);

            if(dataToWrite.isEmpty())
                cvWrite.wait(&mutexWrite);
            
            data = dataToWrite.dequeue();
        }
               
        ret = WriteFile(*hDev, data.data(), data.size(), &bytesWritten, &oWrite);

        if (!ret)
        {
            DWORD err = GetLastError();
            qDebug() << "USBDataWriter WriteFile failed. Error:" << err;
            emit writeError();
        }
        else if (bytesWritten != static_cast<DWORD>(data.size()))
        {
            qDebug() << "USBDataWriter: Not all bytes written. Expected:"
                << data.size() << ", Actual:" << bytesWritten;
            emit writeError();
        }
        else
        {
            qDebug() << "USBDataWriter: Successfully written" << bytesWritten << "bytes";            
        }
    }
}
//------------------------------------------------------------------------------
void USBDataWriter::stop()
{
    active = false;
}
//------------------------------------------------------------------------------