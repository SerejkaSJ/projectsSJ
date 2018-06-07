#include "ProcessWindow.h"

ProcessWindow::ProcessWindow(QWidget* parent) : QWidget(parent)
{
	init();

	setWindowTitle("Select process");
	resize(QSize(300, 100));
}

void ProcessWindow::init()
{
	mainLayout = new QGridLayout();

	initInterface();
}

void ProcessWindow::initInterface()
{
	QMessageBox msgBox;
	msgBox.setText("initInterface.");
	msgBox.exec();
	outputGroup = new QGroupBox("", this);
	QGridLayout* outputLayout = new QGridLayout;

	QLabel* processLabel = new QLabel(this);
	processLabel->setText("Process:");
	outputLayout->addWidget(processLabel, 0, 0);

	QLabel* argumentsLabel = new QLabel(this);
	argumentsLabel->setText("Arguments:");
	outputLayout->addWidget(argumentsLabel, 1, 0);

	output = new QLineEdit();
	output->setReadOnly(1);
	outputLayout->addWidget(output, 0, 1);

	argument = new QLineEdit();
	outputLayout->addWidget(argument, 1, 1);

	selectProcessBtn = new QPushButton(QPixmap(""), QString("Select process"), this);
	outputLayout->addWidget(selectProcessBtn, 0, 2);
	connect(selectProcessBtn, SIGNAL(pressed()), SLOT(slotOpenProcess()));

	okBtn = new QPushButton(QPixmap(""), QString("OK"), this);
	outputLayout->addWidget(okBtn, 1, 2);
	connect(okBtn, SIGNAL(pressed()), SLOT(slotOK()));

	cancelBtn = new QPushButton(QPixmap(""), QString("Cancel"), this);
	outputLayout->addWidget(cancelBtn, 2, 2);
	connect(cancelBtn, SIGNAL(pressed()), SLOT(close()));

	outputGroup->setLayout(outputLayout);
	mainLayout->addWidget(outputGroup, 0, 0);
}

void ProcessWindow::slotOK()
{
	QMessageBox msgBox;
	msgBox.setText("SlotOk.");
	msgBox.exec();

	programPath = output->text();
	arguments = argument->text();

	emit signalOK();

	this->close();
}

void ProcessWindow::slotOpenProcess()
{
	QMessageBox msgBox;
	msgBox.setText("slotOpenProcess.");
	msgBox.exec();
	QString selectedPath = QFileDialog::getOpenFileName(this,
		"Select",
		"",
		"EXE (*.exe)");

	if (selectedPath.isEmpty()) return;

	output->setText(selectedPath);
}

void ProcessWindow::start()
{
	QMessageBox msgBox;
	msgBox.setText("start.");
	msgBox.exec();
	show();
}
