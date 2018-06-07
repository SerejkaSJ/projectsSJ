#include "head.h"
#include "head_render.h"
//#include "render.cpp"

myWindow::myWindow(QWidget *parent) : QWidget(parent)
{
		//qDebug()<<"I'm sorry"<<endl;

	upload=new QPushButton("Upload");
	upload->setObjectName("upload");
	clear=new QPushButton("Clear");
	clear->setObjectName("clear");
	data=new QPushButton("Data");
	data->setObjectName("data");
	delet=new QPushButton("Delete");
	delet->setObjectName("delet");
	text=new QTextEdit();
	text1 = new QTextEdit();
	renderArea=new RenderArea;

QGridLayout * grid = new QGridLayout();

grid->addWidget(renderArea, 0, 0, 4, 1);
grid->addWidget(text1, 4,0, 4, 1);
grid->addWidget(clear,0,1);
grid->addWidget(data,1,1);
grid->addWidget(delet,2,1);
grid->addWidget(upload, 4, 2, 4, 2);//0,1
grid->addWidget(text, 0, 2, 4, 1);
setLayout(grid);

serial= new QSerialPort(this);

openport();
connect(data,SIGNAL(clicked()),this,SLOT(comport()));
connect(upload, SIGNAL(clicked()), this, SLOT(comport()));
connect(clear, SIGNAL(clicked()), this, SLOT(comport()));
connect(delet, SIGNAL(clicked()), this, SLOT(comport()));

setMouseTracking(true);
};

void myWindow::openport()
{
	serial->setPortName("COM3");
	serial->open(QIODevice::ReadWrite);
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);
	serial->clear();
}
void myWindow::comport(){

	QAction* a = qobject_cast< QAction* >(sender());
	QString str; QByteArray arr;
	str = QObject::sender()->objectName();

    if (str == "data") arr = "*";
	if (str == "upload") arr = "1";
	/*{
		qDebug << QString("%1").arg(4) << endl;
	}*/
	if (str == "clear")
	{
	//	RenderArea.createSpell[1] = 0;


	}
	if (str == "delet") arr = "!";
	if (serial->isOpen() && serial->isWritable()) 
	{
	serial->write(arr);
	}

	serial->waitForBytesWritten(-1);
}