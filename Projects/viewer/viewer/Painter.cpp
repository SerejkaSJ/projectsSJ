#include "Painter.h"

#include "header.h"

Painter::Painter(QWidget* parent) 
:QWidget(parent),
 mParent(parent)
{
	init();
}

void Painter::init(){
	qDebug() << "Work";
	/*QPainter painter(this);
	
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
	// painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	painter.drawEllipse(10, 10, 200, 200);
	painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	painter.drawEllipse(100, 3, 20, 20);//1
	painter.drawEllipse(100, 200, 20, 20);//3
	painter.drawEllipse(200, 100, 20, 20);//2
	painter.drawEllipse(0, 100, 20, 20);//4
	painter.drawEllipse(100, 100, 20, 20);//5*/

};


void Painter::paintEvent(QPaintEvent *evt) {
	QPainter paint(this);

	//paint.drawRect(0, 0, 50, 50);
	//paint.drawRect(390, 140, 420, 160);

	myWindow * pWindow = dynamic_cast <myWindow *> (mParent);
	int side = pWindow->side;
	if (rep==true) {
		cout << pWindow->gates.size() << endl;
		for (int i = 0; i < pWindow->gates.size(); i++) {
			//cout << pWindow->gates[i]->name << endl;
		
			int x = pWindow->gates[i]->location.x;
			int y = pWindow->gates[i]->location.y;
			cout << "X: " << x << "Y: " << y << endl;
			if (pWindow->gates[i]->type == 2) {
				paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
				paint.drawEllipse(x, y, side, side);
				paint.drawText(x, y, pWindow->gates[i]->name.c_str());
				paint.setBrush(Qt::NoBrush);
			}
			if (pWindow->gates[i]->type == 3)
			{
				paint.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
				paint.drawRect(x, y, side, side);
				paint.drawText(x, y, pWindow->gates[i]->name.c_str());
				paint.setBrush(Qt::NoBrush);
			}
			if (pWindow->gates[i]->type == 1)
			{
				paint.setBrush(QBrush(Qt::red, Qt::SolidPattern));
				paint.drawRect(x, y, side, side);
				paint.drawText(x, y, pWindow->gates[i]->name.c_str());
				paint.setBrush(Qt::NoBrush);
			}

		}
	}
	
}


void Painter::RenderScheme() {
	qDebug() << "Render" << endl;
	rep = true;
	repaint();

}