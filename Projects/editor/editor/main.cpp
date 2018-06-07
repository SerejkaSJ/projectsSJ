#include "MyWindow.h"

#if defined (_DEBUG) 
#pragma comment(lib, "Qt5Cored.lib") 
#pragma comment(lib, "Qt5Widgetsd.lib") 
#pragma comment(lib, "Qt5SerialPortd.lib") 
#pragma comment(lib, "Qt5Guid.lib") 
#else 
#pragma comment(lib, "Qt5Core.lib") 
#pragma comment(lib, "Qt5Widgets.lib") 
#pragma comment(lib, "Qt5SerialPort.lib") 
#pragma comment(lib, "Qt5Gui.lib") 
#endif
/*
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFont f = a.font();

	MyWindow w;
	w.show();

	return a.exec();
}
*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyWindow w;

	w.show();

	LoadingWidget* lw = new LoadingWidget();
	lw->start();

	return a.exec();
}
