#include "USBDataReader.h"

USBDataReader::USBDataReader(HANDLE fileID, int len_package, QWaitCondition* dataReady)
    : fileID_(fileID), len_package_(len_package), dataReady_(dataReady)
{
    oRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (oRead.hEvent == NULL)
    {
        qDebug() << "USBDataReader CreateEvent failed: " << GetLastError();
        throw std::invalid_argument("USBDataReader CreateEvent failed");
    }
}

USBDataReader::~USBDataReader()
{
    CloseHandle(oRead.hEvent);
}

void USBDataReader::run()
{
    BYTE reportread[256]; // Adjust size as needed
    DWORD bytesRead;

    while (!stopFlag_) // Используйте флаг для graceful shutdown
    {
        // Асинхронное чтение
        if (!ReadFile(fileID_, reportread, len_package_ + 1, NULL, &oRead))
        {
            DWORD error = GetLastError();
            if (error != ERROR_IO_PENDING) {
                qDebug() << "ReadFile failed:" << error;
                break;
            }

            // Ожидаем завершение операции с таймаутом
            DWORD waitResult = WaitForSingleObject(oRead.hEvent, 100);
            if (waitResult == WAIT_OBJECT_0)
            {
                if (!GetOverlappedResult(fileID_, &oRead, &bytesRead, FALSE))
                {
                    qDebug() << "USBDataReader GetOverlappedResult failed:" << GetLastError();
                }

                // Обработка успешно прочитанных данных
                processData(reportread, bytesRead);
            }
            else if (waitResult != WAIT_TIMEOUT)
            {
                qDebug() << "USBDataReader Wait failed:" << GetLastError();
            }
        }
        else
        {
            // Синхронное завершение (редкий случай)
            bytesRead = oRead.InternalHigh;
            processData(reportread, bytesRead);
        }
    }
}


void USBDataReader::processData(const BYTE* data, DWORD size)
{
    QByteArray byteArray(reinterpret_cast<const char*>(data), size);
    {
        QMutexLocker locker(mutex_);
        dataBuffer = byteArray;
    }
    dataReady_->wakeOne();
}