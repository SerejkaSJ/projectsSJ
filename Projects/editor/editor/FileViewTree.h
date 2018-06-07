#ifndef FILE_VIEW_TREE_H
#define FILE_VIEW_TREE_H

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


class FileViewTree : public QTreeWidget
{
	Q_OBJECT


private:
	QList<QTreeWidgetItem*> items;

	QMenu*		contextMenu;
	QAction*		actRemove;

public:
	FileViewTree(QWidget* parent = NULL);

	void init();
	void initMenu();
	void addItem(QString);
	void addItems(QStringList);
	void removeItem(QString);
	void removeItem(int);
	void mouseDoubleClickEvent(QMouseEvent * event);

	public slots:
	void slotCustomContextMenu(const QPoint&);
	void slotRemoveItem();
	void slotItemNameChanged(QTreeWidgetItem*, int);

signals:
	void signalRemoveFile(QString);
	void itemDoubleClicked(QTreeWidgetItem*);
};

#endif   //FILE_VIEW_TREE_H