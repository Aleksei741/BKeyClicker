#include "main.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    QThread* threadButtonProcess = new QThread;
    ButtonProcedure* buttonProcess = new ButtonProcedure();
    buttonProcess->moveToThread(threadButtonProcess);
    QObject::connect(threadButtonProcess, &QThread::started, buttonProcess, &ButtonProcedure::process);
        QObject::connect(buttonProcess, &ButtonProcedure::error,
        [](const QString& msg) {
            qDebug() << "Ошибка:" << msg;
        });
    QObject::connect(buttonProcess, &ButtonProcedure::finished, threadButtonProcess, &QThread::quit);
    QObject::connect(buttonProcess, &ButtonProcedure::finished, buttonProcess, &ButtonProcedure::deleteLater);
    QObject::connect(threadButtonProcess, &QThread::finished, threadButtonProcess, &QThread::deleteLater);
    threadButtonProcess->start();

	MainWindow window(10, 10);
		
	window.show();
	return app.exec();
}