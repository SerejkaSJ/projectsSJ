#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include "head_render.h"

class myWindow: public QWidget
{
	Q_OBJECT
		
public:


	myWindow(QWidget *parent = 0);
QSerialPort *serial;

private:
	void openport();
	RenderArea *renderArea;
	//void PaintEvent(QPaintEvent *event);
	QPushButton *upload;
	QPushButton *clear;
	QPushButton *data;
	QPushButton *delet;


	QTextEdit *text;
	QTextEdit *text1;
	private slots: 
		void comport();
		
		

protected:
	
	
	
};
#endif