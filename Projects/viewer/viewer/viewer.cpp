#include "header.h"

//#include "render.cpp"

myWindow::myWindow(QWidget *parent) : QMainWindow(parent)
{
		setWindowTitle("ViewerNetlist's");
		setMouseTracking(1);

		initActions();
		initMenuBar();
		initToolBar();
		initStatusBar();
		initListElement();
		initViewWidget();
		initCodeWidget();


		//qDebug()<<"I'm sorry"<<endl;

		
}

void myWindow::initViewWidget() {
	widView = new QTabWidget(this);
	widView->setTabsClosable(1);
	widView->setMovable(1);	
	//pic = new Painter(this);
	//widView->addTab(pic, "(untitled)");
	//widView->removeTab(0);
	connect(widView, SIGNAL(tabCloseRequested(int)), SLOT(slotCloseTab(int)));

	this->setCentralWidget(widView);
}
void myWindow::initCodeWidget() {
	
	fileCodeDock = new QDockWidget("Netlist View", this);
	fileCodeDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	fileCodeDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);


	widCode = new QTabWidget(fileCodeDock);
	widCode->setMinimumHeight(200);
	widCode->setTabsClosable(1);
	widCode->setMovable(1);

	editor = new CodeEditor(0, this);
	widCode->addTab(editor, "(untitled)");
	connect(widCode, SIGNAL(tabCloseRequested(int)), SLOT(slotCloseTabCode(int)));
	
	fileCodeDock->setWidget(widCode);
	addDockWidget(Qt::BottomDockWidgetArea, fileCodeDock);
}

  
void myWindow::initListElement()
{
	fileListDock = new QDockWidget("Files View", this);
	fileListDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	fileListDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

	listElement = new ListElement(fileListDock);
	
	//connect(listElement, SIGNAL(signalRemoveFile(QString)), SLOT(slotRemoveFile(QString)));
	//connect(listElement, SIGNAL(itemDoubleClicked(QTreeWidgetItem*)), SLOT(slotDoubleClicked(QTreeWidgetItem*)));

	fileListDock->setWidget(listElement);
	addDockWidget(Qt::LeftDockWidgetArea, fileListDock);
}

void myWindow::initActions()
{//////file///////
	actQuit = new QAction("Quit", this);
	actQuit->setIcon(QPixmap("Resources/Quit.png"));

	actOpen = new QAction("Open", this);
	actOpen->setIcon(QPixmap("Resources/Open.png"));

	actSave = new QAction("Save", this);
	actSave->setIcon(QPixmap("Resources/save.png"));
///////help/////
	actAbout = new QAction("About", this);
	actAbout->setIcon(QPixmap("Resources/about.png"));

	actRender = new QAction("Render", this);
	//actAbout->setIcon(QPixmap("Resources/about.png"));
	connect(actOpen, SIGNAL(triggered()), SLOT(slotOpen()));
	connect(actRender, SIGNAL(triggered()), SLOT(slotRender()));
}
void myWindow::initMenuBar()
{
	menuFile = new QMenu("File");
	menuOptions = new QMenu("Options");
	/*menuEdit = new QMenu("Edit");
	
	menuHelp = new QMenu("Help");
	menuView = new QMenu("View");
	*/

	menuFile->addAction(actOpen);
	menuFile->addAction(actSave);
	menuFile->addAction(actQuit);
	menuFile->addAction(actRender);
	
	menuOptions->addAction(actView);

	//connect(actOpen, SIGNAL(triggered()), SLOT(slotOpen()));
	//connect(actRender, SIGNAL(triggered()), SLOT(slotRender()));
	
	//menuHelp->addAction(actAbout);
	menuBar()->addMenu(menuFile);
	//menuBar()->addMenu(menuEdit);
	menuBar()->addMenu(menuOptions);
	//menuBar()->addMenu(menuHelp);
	
	
}
void myWindow::initToolBar()
{
	toolbar = new QToolBar(this);
	
	toolbar->addAction(actOpen);
	toolbar->addAction(actSave);
	//toolbar->setMovable(1);?????

	addToolBar(Qt::TopToolBarArea, toolbar);
}
void myWindow::initStatusBar()
{
	status = new QStatusBar(this);

	setStatusBar(status);
}
void myWindow::mouseMoveEvent(QMouseEvent* me)
{
	QString mouse_pos = QString("X:%1| Y:%2").arg(me->pos().x()).arg(me->pos().y());

	statusBar()->showMessage(mouse_pos);
}

void myWindow::slotOpen()
{

	QString filename = QFileDialog::getOpenFileName(this,
		"Select",
		"",
		"All (*);; TXT (*.txt);; Netlist's (*.spy *.sp)");
	qDebug() << QString(filename);
	if (filename.isEmpty()) return;
	ElementInLua(filename.toStdString().c_str());
	QString name = filename.split("/").back();
	listElement ->addItem(filename, gates);
	
	
	
	editor->loadFile(filename);
	
	widCode->addTab(editor, name);

	statusBar()->showMessage(QString("File opened: %1").arg(editor->fileName), 3000);

	locationGate();
	cout << "viewer " << gates.size() << endl;
	Painter *pic = new Painter(this);
	widView->addTab(pic, "transistor");
	pic->RenderScheme();
}

void myWindow::slotRender()
{	
	cout<<"render"<<endl;
	qDebug() << "render";
	Painter *test = new Painter(this);
	widView->addTab(test, "transistor");

}

void myWindow::slotCloseTab(int index)
{
	widView->removeTab(index);
}
void myWindow::slotCloseTabCode(int index)
{
	widCode->removeTab(index);
}