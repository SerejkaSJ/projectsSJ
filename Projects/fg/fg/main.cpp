
#include "head.h"

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

QT_USE_NAMESPACE

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  myWindow *window = new myWindow();
  window->resize(700,300);//700/300
  window->show();
  /*
  QLabel lb1("Hello world");
  lb1.show();*/
  /*QDialog *dialog = new QDialog;
  QLabel *label = new QLabel(dialog);
  label->setText("<font color=red>Hello, World!</font>");
  dialog->show();*/
  return app.exec();
}
