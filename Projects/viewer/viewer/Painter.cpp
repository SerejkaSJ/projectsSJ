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
	myWindow * pWindow = dynamic_cast <myWindow *> (mParent);
	if (rep==true) {
		cout << pWindow->gates.size() << endl;
		for (int i = 0; i < pWindow->gates.size(); i++) {
			//cout << pWindow->gates[i]->name << endl;
			int x = pWindow->gates[i]->location.x;
			int y = pWindow->gates[i]->location.y;
			cout << "X: " << x << "Y: " << y << endl;
			if (pWindow->gates[i]->type == 2) {
				paintTwoOutElements(&paint, x, y,"&");
				//paint.drawText(x, y, pWindow->gates[i]->name.c_str());
				//paint.drawText(x, y, pWindow->gates[i]->location.w.c_str());
			}
			if (pWindow->gates[i]->type == 3)
			{
				paintTwoOutElements(&paint, x, y, "1");
				paint.drawText(x, y, pWindow->gates[i]->name.c_str());
			}
			if (pWindow->gates[i]->type == 1)
			{
				paintNot(&paint, x, y);
				paint.drawText(x, y, pWindow->gates[i]->name.c_str());
			}
		}
	}
	
}

void Painter::paintTwoOutElements(QPainter *paint, int x, int y, QString str) {
	int width = 30;
	int height = 40;
	QFont f = paint->font();
	QPen p = paint->pen();
	paint->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	paint->setFont(QFont("Times", 15));
	paint->drawRect(x, y, width, height);
	paint->drawEllipse(x + width + 1, y + (height / 2) - 5, 10, 10);
	paint->drawLine(x + width + 11, y + (height / 2), x + width + 20, y + (height / 2));
	paint->drawText(x + width * 0.25, y + height / 2, str);
	paint->drawLine(x, y + (height *0.75), x - 10, y + (height *0.75));
	paint->drawLine(x, y + (height *0.25), x - 10, y + (height *0.25));
	paint->setFont(f);
	paint->setPen(p);
}


void Painter::paintNot(QPainter *paint,  int x, int y) {
	int width = 30;
	int height = 40;
	QFont f = paint->font();
	QPen p = paint->pen();
	QPen pen(Qt::black, 2, Qt::SolidLine);
	QFont font("Times", 15);
	paint->setPen(pen);
	paint->setFont(font);
	paint->drawRect(x, y, width, height);
	paint->drawEllipse(x+width+1, y+(height/2)-5, 10, 10);
	paint->drawLine(x + width + 11, y + (height / 2), x + width + 20, y + (height / 2));
	paint->drawLine(x, y + (height / 2), x - 10, y + (height / 2));
	paint->drawText(x+ width*0.25, y+height/2,"1");
	paint->setFont(f);
	paint->setPen(p);
}
	
/*void Painter::paintTransistorN(QPainter *paint, int x, int y){
	int dx = 7, dy = 15;
	QPolygonF tran;
	QPolygonF sub;

	tran << QPoint(x, y) << QPoint(x, y + dy) << QPoint(x - dx, y + dy) <<
		QPoint(x - dx, y + 2 * dy) << QPoint(x, y + 2 * dy) << QPoint(x, y + 3 * dy);//tran n
	sub << QPoint(x - dx, y + 1.5 * dy) << QPoint(x + dx, y + 1.5 * dy) << QPoint(x + dx, y);
	paint->drawPolyline(tran);
	paint->drawPolyline(sub);

}
*/
void Painter::RenderScheme() {
	qDebug() << "Render" << endl;
	rep = true;
	repaint();

}
