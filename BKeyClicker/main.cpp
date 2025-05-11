#include "main.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow window(10, 10);
		
	window.show();
	return app.exec();
}