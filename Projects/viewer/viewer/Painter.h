#pragma once
#ifndef RENDER_H
#define RENDER_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>

class Painter : public QWidget
{
	Q_OBJECT

	QWidget * mParent;
public:
	Painter(QWidget * parent = NULL);
	//QPainter *paint;
	void init();
	bool rep = false;
	void RenderScheme();
	//void paintTransistorN(QPainter *paint, int x, int y);
public slots:
	void paintEvent(QPaintEvent *evt);
	
};



#endif