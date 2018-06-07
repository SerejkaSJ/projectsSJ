
#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "CodeEditor.h"
#include "FileViewTree.h"
#include "ProcessWindow.h"
#include "LoadWidget.h"

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


class MyWindow : public QMainWindow
{
	Q_OBJECT

private:
	QString			programPath;

	QDockWidget*	fileViewDock;
	FileViewTree*	fileViewTree;

	QTabWidget*		widTab;

	CodeEditor*		processOutput;

	//----------Menu----------//
	QMenu*			menuFile;
	QAction*		actNew;
	QAction*		actOpen;
	QAction*		actSave;
	QAction*		actSaveAs;
	QAction*		actSaveAll;
	QAction*		actQuit;

	QMenu*			menuRun;
	QAction*		actRun;

	QMenu*			menuSettings;
	QAction*		actProcess;

	QProcess*		programProcess;
	QStringList		arguments;
	ProcessWindow*	pw;
	int				numOfErrors,
		numOfWarnings;

public:
	MyWindow(QWidget* parent = 0);

private:
	void init();
	void initTabWidget();
	void initFileView();
	void initSelectProcess();
	void initShortcuts();
	void initToolBars();
	void initMenuBar();
	void initStatusBar();
	void initProcess();
	void initProcessOutput();

	void addHighlightningRules(CodeEditor* editor);

	private slots:
	void slotNew();
	void slotOpen();
	void slotSave();
	void slotSaveAs();
	void slotSaveAll();
	void slotRun();

	void slotRemoveFile(QString);
	void slotDoubleClicked(QTreeWidgetItem*);
	void slotCloseTab(int);

	void slotReadSatndartOutput();
	void slotReadErrorOutput();
	void slotProcessStarted();
	void slotProcessFinished(int, QProcess::ExitStatus);

	void slotSelectProcess();
	void slotGetProcess();
};

#endif