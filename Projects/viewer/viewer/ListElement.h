#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "ElementInLua.h"


#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

//#include "MyWindow.h"

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>


class ListElement : public QTreeWidget
{
	Q_OBJECT


private:
	QList<QTreeWidgetItem*> items;

	QMenu*		contextMenu;
	QAction*		actRemove;

public:
	ListElement(QWidget* parent = NULL);

	void init();
	void addItem(QString, vector<Gate*> gates);
//	void addItem(QString);
};

#endif   //LIST_ELEMENT_H