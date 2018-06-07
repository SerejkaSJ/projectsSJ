#include "Header.h"



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
#pragma comment(lib, "lua53.lib") 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyCalculator w;
	w.setStyleSheet("QWidget { background-color:"
		"qlineargradient(x1:0, y1:1, x2:0, y2:0, "
		"stop:1 rgb(195, 142, 99), "
		" stop:0.4 rgb(238, 197, 169) ) }");


	w.show();
	return a.exec();
}