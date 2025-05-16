#include "USBDataWriter.h"

USBDataWriter::USBDataWriter(HANDLE fileID, QMutex* mutex, QWaitCondition* dataReady)
    : fileID_(fileID), mutex_(mutex), dataReady_(dataReady) 
{

}

void USBDataWriter::run() override
{
    while (true) {
        mutex_->lock();
        dataReady_->wait(mutex_);  // Wait for data to be available
        QByteArray data = dataToWrite;  // Get data to write
        mutex_->unlock();

        if (data.isEmpty()) break;  // Check for stop condition

        DWORD bytesWritten;
        BOOL success = WriteFile(fileID_, data.data(), data.size(), &bytesWritten, NULL);
        if (!success) {
            qDebug() << "USBDataWriter WriteFile failed:" << GetLastError();
            break;
        }
    }
}