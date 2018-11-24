#include "ElementInLua.h"
#include "CodeEditor.h"
#include "Painter.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include "ElementInLua.h"
#include "ListElement.h"
#include <iostream>
#include <vector> 

#pragma comment(lib, "lua53.lib") 

using namespace std;
using namespace luabridge;

#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtWidgets/QAbstractScrollArea>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QShortCut>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>


class myWindow : public QMainWindow
{
	Q_OBJECT

public:
	myWindow(QWidget *parent = 0);
	Transistor *transistor;
	Painter *painter;
	QDockWidget*	fileListDock;
	ListElement *listElement;

	int x_cord = 425, y_cord = 250;
	int side = 40;
	bool logicView = true;
	bool transistorView = false;
	QDockWidget*	fileCodeDock;
	QTabWidget*		widView;
	QTabWidget*		widCode;
	vector<Gate*> gates;
	CodeEditor* editor;
private:

	vector<Transistor*> transistors;
	vector<Net*> nets;
	QAction* actQuit;
	QAction* actOpen;
	QAction* actSave;
	QAction* actAbout;
	QAction* actRender;
	QAction* actView;
	QMenu* menuFile;
	QMenu* menuEdit;
	QMenu* menuOptions;
	QMenu* menuHelp;
	QMenu* menuView;
	QToolBar* toolbar;
	QStatusBar* status;
	
	//////////////////
	void initActions();
	void initMenuBar();
	void initToolBar();
	void initStatusBar();
	void initElement();
	void initListElement();
	void initViewWidget();
	void initCodeWidget();
	void addHighlightningRules(CodeEditor* editor);
protected:
	void mouseMoveEvent(QMouseEvent* me);

	void AddTransistor(string name, string drain, string gate, string source, string substrate, string type);
	Gate * AddGate(string name, GateType type);
	int ElementInLua(string pathFile);
	int locationGate();
	vector<int> FindOutElement();
	vector<int> FindNetsElement(vector<int>  chekLevel);
	void scaleElements(vector<vector<int>>  levels);
public slots:
	void slotOpen();
	void slotRender();
	void slotCloseTab(int);
	void slotCloseTabCode(int);

};
#endif
