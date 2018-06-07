#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H
//include "MyWindow.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <vector>
#include <cmath>
#include <ctime>
#include <math.h>

using namespace std;

class ProcessWindow : public QWidget
{
	Q_OBJECT

private:
	QAction*		actQuit;
	QAction*		standartTheme;
	QAction*		genTheme;

	QGroupBox*		outputGroup;

	QGridLayout*	mainLayout;
	QLineEdit*		output;
	QLineEdit*		argument;

	QPushButton*	okBtn;
	QPushButton*	cancelBtn;
	QPushButton*	selectProcessBtn;

public:
	ProcessWindow(QWidget *parent = NULL);

	void			init();
	void			start();

	void			initInterface();
	QString			programPath;
	QString			arguments;

	public slots:
	void slotOpenProcess();
	void slotOK();

signals:
	void signalOK();
};

#endif