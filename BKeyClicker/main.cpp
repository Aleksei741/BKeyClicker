#include "main.h"

QVector<ButtonFTimer_DType> OptButonTimer = QVector<ButtonFTimer_DType>(10);
QVector<ButtonFCondition_DType> OptButtonFCondition = QVector<ButtonFCondition_DType>(10);

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    QThread* threadUSBProcess = new QThread;
    USBProcedure* USBProcess = new USBProcedure();
    USBProcess->moveToThread(threadUSBProcess);
    QObject::connect(threadUSBProcess, &QThread::started, USBProcess, &USBProcedure::process);
    QObject::connect(USBProcess, &USBProcedure::finished, threadUSBProcess, &QThread::quit);
    QObject::connect(USBProcess, &USBProcedure::finished, USBProcess, &USBProcedure::deleteLater);
    QObject::connect(threadUSBProcess, &QThread::finished, threadUSBProcess, &QThread::deleteLater);
    threadUSBProcess->start();

    QThread* threadButtonProcess = new QThread;
    ButtonProcedure* buttonProcess = new ButtonProcedure();
    buttonProcess->moveToThread(threadButtonProcess);
    QObject::connect(threadButtonProcess, &QThread::started, buttonProcess, &ButtonProcedure::process);
    QObject::connect(buttonProcess, &ButtonProcedure::finished, threadButtonProcess, &QThread::quit);
    QObject::connect(buttonProcess, &ButtonProcedure::finished, buttonProcess, &ButtonProcedure::deleteLater);
    QObject::connect(threadButtonProcess, &QThread::finished, threadButtonProcess, &QThread::deleteLater);
    threadButtonProcess->start();

	MainWindow window(10, 10);
    QObject::connect(USBProcess, &USBProcedure::GUISetStatusConection, &window, &MainWindow::handleStatusConnection);
		
	window.show();
	return app.exec();
}