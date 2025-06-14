#include "USBDataWriter.h"

USBDataWriter::USBDataWriter(HANDLE* hDev_)
    : hDev(hDev_)
{
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
    QMutexLocker locker(&mutexWrite);
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
            QMutexLocker locker(&mutexWrite);

            if(dataToWrite.isEmpty())
                cvWrite.wait(&mutexWrite);
            
            if (!dataToWrite.isEmpty())
                data = dataToWrite.dequeue();
            else
            {
                data.clear();
            }
        }
        
        if (!data.isEmpty())
        {
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

    qDebug() << "USBDataWriter process stop.";
    emit finished();
}
//------------------------------------------------------------------------------
void USBDataWriter::stop()
{
    active = false;
    cvWrite.notify_all();
}
//------------------------------------------------------------------------------