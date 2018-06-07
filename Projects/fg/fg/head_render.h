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

class RenderArea : public QWidget
{
	Q_OBJECT

public:
	RenderArea(QWidget *parent = 0);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent* event);
	int i = 0;
	int *createSpell = new int[i];
protected:
	

};







#endif