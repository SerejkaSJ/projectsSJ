#ifndef LOAD_WIDGET_H
#define LOAD_WIDGET_H

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
#include <QtWidgets/QAbstractScrollArea>
#include <QtGui/QPainter>
#include <QtGui/QMovie>
#include <QtCore/QDebug>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>

class LoadingWidget : public QWidget
{
	Q_OBJECT

		QMovie* movie;
	QLabel* movieLabel;
	QLabel* label;

public:
	LoadingWidget(QWidget* parent = NULL);
	void start();

private:
	void init();

};

#endif