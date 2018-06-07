#ifndef MYCALCULATOR_H
#define MYCALCULATOR_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
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

#include <iostream>
#include <lua.hpp>
#include <LuaBridge.h>


class MyCalculator : public QMainWindow
{
	Q_OBJECT

private:
	
	//QApplication* w;
	QLineEdit* resultLine;
	QGridLayout* mainLayout;
	QLineEdit* output;
	QGroupBox* digitsGroup;
	QPushButton* digits[20];

public:
	MyCalculator(QWidget *parent = 0);
	QAction* actQuit;
	QAction* actGen;
	QAction* actStandart;
	QGridLayout* digitsLayout;

	


	void init();
	void initMenuBar();
	void initToolBar();
	void initStatusBar();
	


	void initInterface();
	void initLCD();
	//void initDigits();


	public slots:
	void slotEnterDigit();
	void slotEnterEqually();
	void genScheme();
	void standartScheme();
	void initDigits();
	void slotDel();
	void slotBackSpace();
protected:
	virtual void keyPressEvent(QKeyEvent *event);

};
#endif // MYCALCULATOR_H

