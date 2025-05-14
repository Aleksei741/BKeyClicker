#include "main.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QThread* threadButtonProcess = new QThread;
	ButtonProcedure* ButtonProcess = new ButtonProcedure();
	ButtonProcess->moveToThread(threadButtonProcess);
	connect(ButtonProcess, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(threadButtonProcess, SIGNAL(started()), ButtonProcess, SLOT(process()));
	connect(ButtonProcess, SIGNAL(finished()), threadButtonProcess, SLOT(quit()));
	connect(ButtonProcess, SIGNAL(finished()), ButtonProcess, SLOT(deleteLater()));
	connect(threadButtonProcess, SIGNAL(finished()), threadButtonProcess, SLOT(deleteLater()));
	threadButtonProcess->start();


	MainWindow window(10, 10);
		
	window.show();
	return app.exec();
}