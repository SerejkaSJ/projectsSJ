#include "Header.h"

#include <iostream>
#include <lua.hpp>
#include <LuaBridge.h>
using namespace std;


MyCalculator::MyCalculator(QWidget *parent) : QMainWindow(parent)
{
	init();

	setWindowTitle("Calculator");
	resize(QSize(250, 200));

	show();
}

void MyCalculator::init() {
	QWidget* w = new QWidget;
	mainLayout = new QGridLayout();

	initMenuBar();
	initInterface();
	initToolBar();
	initStatusBar();

	w->setLayout(mainLayout);
	setCentralWidget(w);
}


void MyCalculator::initMenuBar() {
	QMenu* mFile = new QMenu("File", this);
	QMenu* mView = new QMenu("View", this);

	 actQuit = new QAction(QPixmap(), "Quit", this);
	 actGen = new QAction(QPixmap(), "Generation Theme", this);
	 actStandart = new QAction(QPixmap(), "Standart Theme", this);

	connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(actGen, SIGNAL(triggered()), this, SLOT(genScheme()));
	connect(actStandart, SIGNAL(triggered()), this, SLOT(standartScheme()));

	mFile->addAction(actQuit);
	mView->addAction(actGen);
	mView->addAction(actStandart);
	menuBar()->addMenu(mFile);
	menuBar()->addMenu(mView);
	menuBar()->setStatusTip("Menu");
	mView->setStatusTip("Scheme");
	actGen->setStatusTip("Generate Scheme");
	actStandart->setStatusTip("Standart Scheme");
}

void MyCalculator::initToolBar() {
	QToolBar* toolbar = new QToolBar(this);

	actQuit->setIcon(QPixmap("exit.png"));

	toolbar->addAction(actQuit);
	toolbar->addAction(actGen);
	toolbar->addAction(actStandart);
	toolbar->setMovable(1);

	addToolBar(Qt::TopToolBarArea, toolbar);
}
void MyCalculator::initStatusBar()
{
	QStatusBar* status = new QStatusBar(this);

	setStatusBar(status);

	//status->showMessage("Welcome to gorgorod");
	status->setStatusTip("Status bar");
}

void MyCalculator::initInterface() {
	initLCD();
	initDigits();
}
void MyCalculator::initLCD() {
	QGroupBox* outputGroup = new QGroupBox("Output", this);
	QVBoxLayout* outputLayout = new QVBoxLayout;

	output = new QLineEdit();
	output->setAlignment(Qt::AlignRight);
	output->setReadOnly(1);
	output->setPlaceholderText("Output...");
	outputLayout->addWidget(output);

	outputGroup->setLayout(outputLayout);

	mainLayout->addWidget(outputGroup, 0, 0);
}
void MyCalculator::initDigits() {
	QGroupBox* digitsGroup = new QGroupBox("");
	 digitsLayout = new QGridLayout;

	digits[0] = new QPushButton(QPixmap(""), QString("0"), this);
	digitsLayout->addWidget(digits[0], 5, 1, 1, 2);
	connect(digits[0], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[1] = new QPushButton(QPixmap(""), QString("1"), this);
	digitsLayout->addWidget(digits[1], 4, 1);
	connect(digits[1], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[2] = new QPushButton(QPixmap(""), QString("2"), this);
	digitsLayout->addWidget(digits[2], 4, 2);
	connect(digits[2], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[3] = new QPushButton(QPixmap(""), QString("3"), this);
	digitsLayout->addWidget(digits[3], 4, 3);
	connect(digits[3], SIGNAL(pressed()), SLOT(slotEnterDigit()));
	
	digits[4] = new QPushButton(QPixmap(""), QString("4"), this);
	digitsLayout->addWidget(digits[4], 3, 1);
	connect(digits[4], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[5] = new QPushButton(QPixmap(""), QString("5"), this);
	digitsLayout->addWidget(digits[5], 3, 2);
	connect(digits[5], SIGNAL(pressed()), SLOT(slotEnterDigit()));
	
	digits[6] = new QPushButton(QPixmap(""), QString("6"), this);
	digitsLayout->addWidget(digits[6], 3, 3);
	connect(digits[6], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[7] = new QPushButton(QPixmap(""), QString("7"), this);
	digitsLayout->addWidget(digits[7], 2, 1);
	connect(digits[7], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[8] = new QPushButton(QPixmap(""), QString("8"), this);
	digitsLayout->addWidget(digits[8], 2, 2);
	connect(digits[8], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[9] = new QPushButton(QPixmap(""), QString("9"), this);
	digitsLayout->addWidget(digits[9], 2, 3);
	connect(digits[9], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[10] = new QPushButton(QPixmap(""), QString("."), this);
	digitsLayout->addWidget(digits[10], 5, 3,1, 1);
	connect(digits[10], SIGNAL(pressed()), SLOT(slotEnterDigit()));
	
	digits[11] = new QPushButton(QPixmap(""), QString("="), this);
	digitsLayout->addWidget(digits[11], 5, 4, 1, 1);
	connect(digits[11], SIGNAL(pressed()), SLOT(slotEnterEqually()));

	digits[12] = new QPushButton(QPixmap(""), QString("+"), this);
	digitsLayout->addWidget(digits[12], 4, 4);
	connect(digits[12], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[13] = new QPushButton(QPixmap(""), QString("-"), this);
	digitsLayout->addWidget(digits[13], 3, 4);
	connect(digits[13], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[14] = new QPushButton(QPixmap(""), QString("*"), this);
	digitsLayout->addWidget(digits[14], 2, 4);
	connect(digits[14], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[15] = new QPushButton(QPixmap(""), QString("/"), this);
	digitsLayout->addWidget(digits[15], 1, 4);
	connect(digits[15], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[16] = new QPushButton(QPixmap(""), QString(""), this);
	digits[16]->setIcon(QPixmap("Resources/back.png"));
	digitsLayout->addWidget(digits[16], 1, 3);
	connect(digits[16], SIGNAL(pressed()), SLOT(slotBackSpace()));

	digits[17] = new QPushButton(QPixmap(""), QString("^"), this);
	digitsLayout->addWidget(digits[17], 1, 2);
	connect(digits[17], SIGNAL(pressed()), SLOT(slotEnterDigit()));

	digits[18] = new QPushButton(QPixmap(""), QString("CE"), this);
	digitsLayout->addWidget(digits[18], 1, 1);
	connect(digits[18], SIGNAL(pressed()), SLOT(slotDel()));
	
	digitsGroup->setLayout(digitsLayout);
	mainLayout->addWidget(digitsGroup, 1, 0);
}
void MyCalculator::standartScheme() {
	initLCD();
	initDigits();
	menuBar()->setStatusTip("Standart Scheme");
}
void MyCalculator::genScheme() {
	QString  str = QString("QPushButton{background-color:qlineargradient(x1:0,y1:1,x2:0,y2:0,stop:1 rgb(%1,%2,%3),stop:0.4 rgb(%4,%5,%6))}").arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255);
	for (int i = 0; i <= 18; i++)
	{
		digits[i]->setStyleSheet(str);
	}
	QString  str1 = QString("QLineEdit {color: rgb(%1,%2,%3);background-color:rgb(%4,%5,%6)}").arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255);
	output->setStyleSheet(str1);

	this->update();
	menuBar()->setStatusTip("Generate Scheme");
}


void MyCalculator::slotEnterDigit() {
	QString str = ((QPushButton*)sender())->text();
	QString out = QString("%1%2").arg(output->text()).arg(str);
	output->setText(out);

	if (out.size() > 15)
	{
		QMessageBox msgBox;
		msgBox.setText("Stop");
		msgBox.exec();
		 out.clear();
		 output->setText(out);
	}
}

void MyCalculator::slotEnterEqually() {
	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "calculator.lua");
	

	luabridge::LuaRef sumNumbers = luabridge::getGlobal(L, "calculator");
    std::string s =  sumNumbers(output->text().toStdString().c_str());
	cout << s << endl;
	QString result = s.c_str();
	QString out = " ";
	output->setText(result);
}

void MyCalculator::slotBackSpace()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "delete.lua");


	luabridge::LuaRef sumNumber = luabridge::getGlobal(L, "delete");
	std::string s = sumNumber(output->text().toStdString().c_str());
	cout << s <<"  work" <<endl;
	QString result = s.c_str();
	QString out = " ";
	output->setText(result);
}

void MyCalculator::slotDel() {
	QString out = " ";
	out.clear();
	output->setText(out);

}
void MyCalculator::keyPressEvent(QKeyEvent *event) {
	int key = event->key();
	cout << key;
		if (key >= Qt::Key_0 && key <= Qt::Key_9) { //Цифровые клавиши 0..9
			QString str = QString(QChar(key));
			QString out = QString("%1%2").arg(output->text()).arg(str);
			output->setText(out);
			if (out.size() > 15)
			{
				QMessageBox msgBox;
				msgBox.setText("Stop");
				msgBox.exec();
				out.clear();
				output->setText(out);
			}
		}
		 if (key == Qt::Key_Backspace || key == Qt::Key_Shift) { //BackSpace стирает символ
			cout << "Work";
			lua_State* L = luaL_newstate();
			luaL_openlibs(L);
			luaL_dofile(L, "delete.lua");


			luabridge::LuaRef sumNumber = luabridge::getGlobal(L, "delete");
			std::string s = sumNumber(output->text().toStdString().c_str());
			cout << s << "  work" << endl;
			QString result = s.c_str();
			QString out = " ";
			output->setText(result);
		}

		 if (key == Qt::Key_Plus || key == Qt::Key_Minus || key == Qt::Key_Slash || key == Qt::Key_Asterisk) {
			 QString str = QString(QChar(key));
			 QString out = QString("%1%2").arg(output->text()).arg(str);
			 output->setText(out);
		 }
		 if (key == Qt::Key_Equal || key == Qt::Key_Enter) {
			 lua_State* L = luaL_newstate();
			 luaL_openlibs(L);
			 luaL_dofile(L, "calculator.lua");


			 luabridge::LuaRef sumNumbers = luabridge::getGlobal(L, "calculator");
			 std::string s = sumNumbers(output->text().toStdString().c_str());
			 cout << s << endl;
			 QString result = s.c_str();
			 QString out = " ";
			 output->setText(result);
		 }

}
