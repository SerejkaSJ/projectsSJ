#include "MyWindow.h"


MyWindow::MyWindow(QWidget* parent) : QMainWindow(parent) {
	init();

	this->setWindowTitle("EE - Epic Editor");
	this->resize(QSize(800, 800));
}
void MyWindow::init() {
	initTabWidget();
	initFileView();
	initSelectProcess();
	initShortcuts();
	initMenuBar();
	initToolBars();
	initStatusBar();
	initProcess();
	initProcessOutput();
}
void MyWindow::initTabWidget() {
	widTab = new QTabWidget(this);
	widTab->setTabsClosable(1);
	widTab->setMovable(1);

	connect(widTab, SIGNAL(tabCloseRequested(int)), SLOT(slotCloseTab(int)));

	this->setCentralWidget(widTab);
}
void MyWindow::initFileView()
{
	fileViewDock = new QDockWidget("Files View", this);
	fileViewDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	fileViewDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

	fileViewTree = new FileViewTree(fileViewDock);

	connect(fileViewTree, SIGNAL(signalRemoveFile(QString)), SLOT(slotRemoveFile(QString)));
	connect(fileViewTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*)), SLOT(slotDoubleClicked(QTreeWidgetItem*)));

	fileViewDock->setWidget(fileViewTree);
	addDockWidget(Qt::LeftDockWidgetArea, fileViewDock);
}

void MyWindow::initSelectProcess()
{
	pw = new ProcessWindow();
	connect(pw, SIGNAL(signalOK()), SLOT(slotGetProcess()));
}

void MyWindow::initShortcuts()
{
	this->setShortcutEnabled(1);

	QShortcut* scOpen = new QShortcut(QKeySequence("Ctrl+O"), this);
	QShortcut* scSave = new QShortcut(QKeySequence("Ctrl+S"), this);
	QShortcut* scSaveAs = new QShortcut(QKeySequence("Ctrl+Shift+S"), this);

	connect(scOpen, SIGNAL(activated()), SLOT(slotOpen()));
	connect(scSave, SIGNAL(activated()), SLOT(slotSave()));
	connect(scSaveAs, SIGNAL(activated()), SLOT(slotSaveAs()));
}
void MyWindow::addHighlightningRules(CodeEditor* editor)
{
	QStringList reservedWords;
	reservedWords
		<< "\\bvoid\\b"
		<< "\\bint\\b"
		<< "\\bshort\\b"
		<< "\\blong\\b"
		<< "\\bfloat\\b"
		<< "\\bdouble\\b"
		<< "\\bbool\\b"
		<< "\\bstring\\b"
		<< "\\bchar\\b"
		<< "\\bclass\\b"
		<< "\\bstruct\\b"
		<< "\\bunion\\b"
		<< "\\benum\\b"
		<< "\\b#define\\b"
		<< "\\b#include\\b"
		<< "\\bthis\\b";

	QString str = "\"([^\"]*)\"";

	QTextCharFormat stringRuleFormat;
	stringRuleFormat.setForeground(QColor(Qt::red).lighter(70));
	editor->highlighter->addHighlightningRule(QRegExp(str), stringRuleFormat);

	QTextCharFormat reservedWordsRuleFormat;
	reservedWordsRuleFormat.setForeground(QColor(Qt::blue).lighter(130));
	foreach(const QString &str, reservedWords) {
		editor->highlighter->addHighlightningRule(QRegExp(str), reservedWordsRuleFormat);
	}

	QTextCharFormat multiLineCommentRuleFormat;
	multiLineCommentRuleFormat.setForeground(QColor(Qt::green).lighter(50));
	editor->highlighter->multilineCommentsEnabled = 1;
	editor->highlighter->multiLineCommentFormat = multiLineCommentRuleFormat;
	editor->highlighter->commentStartExpression = QRegExp("/\\*");
	editor->highlighter->commentEndExpression = QRegExp("\\*/");
}
void MyWindow::initMenuBar()
{
	//Init menu "File"
	menuFile = new QMenu("File");

	actNew = new QAction(QPixmap("Resources/New.png"), "New", this);
	actOpen = new QAction(QPixmap("Resources/Open.png"), "Open File", this);
	actSave = new QAction(QPixmap("Resources/Save.png"), "Save", this);
	actSaveAs = new QAction(QPixmap("Resources/SaveAs.png"), "Save As", this);
	actSaveAll = new QAction(QPixmap("Resources/SaveAll.png"), "Save All", this);
	actQuit = new QAction(QPixmap("Resources/Quit.png"), "Quit", this);

	actNew->setStatusTip("New File");
	actOpen->setStatusTip("Open File");
	actSave->setStatusTip("Save");
	actSaveAs->setStatusTip("Save As");
	actSaveAll->setStatusTip("Save All");
	actQuit->setStatusTip("Quit");

	connect(actNew, SIGNAL(triggered()), SLOT(slotNew()));
	connect(actOpen, SIGNAL(triggered()), SLOT(slotOpen()));
	connect(actSave, SIGNAL(triggered()), SLOT(slotSave()));
	connect(actSaveAs, SIGNAL(triggered()), SLOT(slotSaveAs()));
	connect(actSaveAll, SIGNAL(triggered()), SLOT(slotSaveAll()));
	connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

	menuFile->addAction(actNew);
	menuFile->addAction(actOpen);
	menuFile->addSeparator();
	menuFile->addAction(actSave);
	menuFile->addAction(actSaveAs);
	menuFile->addAction(actSaveAll);
	menuFile->addSeparator();
	menuFile->addAction(actQuit);


	//Init menu "Run"
	menuRun = new QMenu("Run");

	actRun = new QAction(QPixmap("Resources/Run.png"), "Run", this);
	actRun->setStatusTip("Run program");

	connect(actRun, SIGNAL(triggered()), SLOT(slotRun()));

	menuRun->addAction(actRun);

	menuSettings = new QMenu("Settings");

	actProcess = new QAction(QPixmap(), "Process", this);
	actProcess->setStatusTip("Select process");

	menuSettings->addAction(actProcess);

	connect(actProcess, SIGNAL(triggered()), SLOT(slotSelectProcess()));

	//Add menues
	menuBar()->addMenu(menuFile);
	menuBar()->addMenu(menuRun);
	menuBar()->addMenu(menuSettings);
}
void MyWindow::initToolBars()
{
	//Init main toolbar
	QToolBar* mainToolbar = new QToolBar(this);

	mainToolbar->addAction(actOpen);
	mainToolbar->addAction(actSave);
	mainToolbar->addAction(actSaveAs);
	mainToolbar->addAction(actSaveAll);
	mainToolbar->addAction(actQuit);

	//Init run toolbar
	QToolBar* runToolbar = new QToolBar(this);

	runToolbar->addAction(actRun);

	//Add toolbars
	addToolBar(Qt::TopToolBarArea, mainToolbar);
	addToolBar(Qt::TopToolBarArea, runToolbar);
}
void MyWindow::initStatusBar()
{
	QStatusBar* statusbar = new QStatusBar(this);

	setStatusBar(statusbar);
}
void MyWindow::initProcess()
{
	programProcess = new QProcess(this);

	connect(programProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadSatndartOutput()));
	connect(programProcess, SIGNAL(readyReadStandardError()), this, SLOT(slotReadErrorOutput()));
	connect(programProcess, SIGNAL(started()), this, SLOT(slotProcessStarted()));
	connect(programProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinished(int, QProcess::ExitStatus)));

}
void MyWindow::initProcessOutput()
{
	//Init widget
	processOutput = new CodeEditor(1, this);

	QTextCharFormat warningFormat;
	warningFormat.setForeground(QColor(255, 255, 255));
	warningFormat.setBackground(QColor(255, 128, 0));
	processOutput->highlighter->addHighlightningRule(QRegExp(".*warning.*", Qt::CaseInsensitive), warningFormat);

	QTextCharFormat okFormat;
	okFormat.setForeground(QColor(0, 255, 0));
	processOutput->highlighter->addHighlightningRule(QRegExp("\\bok\\b", Qt::CaseInsensitive), okFormat);

	QTextCharFormat errorFormat;
	errorFormat.setForeground(QColor(255, 255, 255));
	errorFormat.setBackground(QColor(255, 0, 0));
	processOutput->highlighter->addHighlightningRule(QRegExp(".*error.*", Qt::CaseInsensitive), errorFormat);

	QTextCharFormat stoppedFormat;
	stoppedFormat.setForeground(QColor(0, 0, 255));
	processOutput->highlighter->addHighlightningRule(QRegExp(".*stopped.*", Qt::CaseInsensitive), stoppedFormat);

	addHighlightningRules(processOutput);

	//Init dock
	QDockWidget* consoleDock = new QDockWidget("Output", this);
	consoleDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	consoleDock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

	consoleDock->setWidget(processOutput);

	addDockWidget(Qt::BottomDockWidgetArea, consoleDock);
}


void MyWindow::slotNew()
{
	CodeEditor* editor = new CodeEditor(0, widTab);
	addHighlightningRules(editor);

	widTab->addTab(editor, "(untitled)");

	statusBar()->showMessage("New file created", 3000);
}
void MyWindow::slotOpen()
{
	QString filename = QFileDialog::getOpenFileName(this,
		"Select",
		"",
		"All (*);; TXT (*.txt);; Source and Headers (*.c *.cpp *.h *.hpp)");

	if (filename.isEmpty()) return;

	QString name = filename.split("/").back();

	CodeEditor* editor = new CodeEditor(0, widTab);
	addHighlightningRules(editor);
	editor->loadFile(filename);

	widTab->addTab(editor, name);

	fileViewTree->addItem(filename);

	statusBar()->showMessage(QString("File opened: %1").arg(editor->fileName), 3000);
}
void MyWindow::slotSave()
{
	CodeEditor* current = (CodeEditor*)widTab->currentWidget();
	if (current == NULL) return;
	current->save();
	statusBar()->showMessage(QString("Saved: %1").arg(current->fileName), 3000);
}
void MyWindow::slotSaveAs()
{
	CodeEditor* current = (CodeEditor*)widTab->currentWidget();
	if (current == NULL) return;
	QString filename = QFileDialog::getSaveFileName();
	if (!filename.isEmpty())
	{
		current->fileName = filename;
		current->save();
		widTab->setTabText(widTab->indexOf(widTab->currentWidget()), current->fileName.split("/").back());
		statusBar()->showMessage(QString("Saved: %1").arg(current->fileName), 3000);
	}
}
void MyWindow::slotSaveAll()
{
	for (int i = 0; i < widTab->count(); i++)
	{
		CodeEditor* current = (CodeEditor*)widTab->widget(i);
		current->save();
		statusBar()->showMessage(QString("Saved all!"));
	}
}
void MyWindow::slotRun() {

	if (programPath.isEmpty() && arguments.empty()) return;

	programProcess->start(programPath, arguments);
}
void MyWindow::slotRemoveFile(QString file)
{
	for (int i = 0; i < widTab->count(); i++)
	{
		if (((CodeEditor*)(widTab->widget(i)))->fileName == file)
		{
			widTab->removeTab(i);
		}
	}
}
void MyWindow::slotDoubleClicked(QTreeWidgetItem* item)
{
	for (int i = 0; i < widTab->count(); i++)
	{
		if (((CodeEditor*)(widTab->widget(i)))->fileName == item->toolTip(0))
		{
			widTab->setCurrentIndex(i);

			return;
		}
	}

	QString name = item->text(0);
	CodeEditor* editor = new CodeEditor(0, widTab);
	addHighlightningRules(editor);
	editor->loadFile(item->toolTip(0));

	widTab->addTab(editor, name);

	statusBar()->showMessage(QString("File opened: %1").arg(editor->fileName), 3000);
}
void MyWindow::slotCloseTab(int index)
{
	widTab->removeTab(index);
}
void MyWindow::slotReadSatndartOutput()
{
	QMessageBox msgBox;
	msgBox.setText("OutPUT.");
	msgBox.exec();

	QByteArray ba = programProcess->readAllStandardOutput();
	QList <QByteArray> list = ba.split('\n');
	list.removeLast();
	foreach(const QByteArray &barray, list)
	{
		QString str = QString::fromLocal8Bit(barray);
		processOutput->appendPlainText(barray.trimmed());

		if (barray.trimmed() == "ERROR")
		{
			numOfErrors++;
		}

		if (barray.trimmed() == "WARNING")
		{
			numOfWarnings++;
		}
	}
	processOutput->verticalScrollBar()->setValue(processOutput->verticalScrollBar()->maximum());
}
void MyWindow::slotReadErrorOutput()
{
	QMessageBox msgBox;
	msgBox.setText("OutPUT.");
	msgBox.exec();

	QByteArray ba = programProcess->readAllStandardError();
	QList <QByteArray> list = ba.split('\n');
	list.removeLast();

	foreach(const QByteArray &barray, list)
	{
		QString str = QString::fromLocal8Bit(barray);
		processOutput->appendPlainText(barray.trimmed());
	}

	processOutput->verticalScrollBar()->setValue(processOutput->verticalScrollBar()->maximum());
	//processOutput->setValue(processOutput->verticalScrollBar()->maximum());
}
void MyWindow::slotProcessStarted()
{
	QMessageBox msgBox;
	msgBox.setText("OutPUT.");
	msgBox.exec();
	actRun->setEnabled(0);

	numOfErrors = 0;
	numOfWarnings = 0;

	processOutput->appendPlainText("");
	processOutput->appendPlainText("Processing...");
	processOutput->appendPlainText("");
}
void MyWindow::slotProcessFinished(int exitCode, QProcess::ExitStatus status)
{
	actRun->setEnabled(1);

	QString exit = QString("Process - [%1]: Code[%2]").arg(status).arg(exitCode);
	processOutput->appendPlainText(exit);

	QString result = QString("Warnings: %1").arg(numOfWarnings);
	processOutput->appendPlainText(result);

	result = QString("Errors: %1").arg(numOfErrors);
	processOutput->appendPlainText(result);

	if (status == QProcess::CrashExit)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Error");
		msgBox.setText("Something goes wrong!");
		msgBox.exec();
	}
}

void MyWindow::slotSelectProcess()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	msgBox.setText("Something goes wrong!");
	msgBox.exec();
	pw->start();
}

void MyWindow::slotGetProcess()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Eor");
	msgBox.setText("Something goes wrong!");
	msgBox.exec();
	programPath = pw->programPath;
	arguments = pw->arguments.split(QRegExp(";"), QString::SkipEmptyParts);
}

