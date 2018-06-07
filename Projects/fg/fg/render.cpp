#include "head_render.h"


RenderArea::RenderArea(QWidget *parent) 
: QWidget(parent) {
setMinimumSize(250, 250); // !!!!!!
}
void RenderArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
	// painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	painter.drawEllipse(10,10,200,200);
	painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	painter.drawEllipse(100,3,20,20);//1
	painter.drawEllipse(100,200,20,20);//3
	painter.drawEllipse(200,100,20,20);//2
	painter.drawEllipse(0,100,20,20);//4
	painter.drawEllipse(100,100,20,20);//5

};
void RenderArea::mousePressEvent(QMouseEvent *event)
{

	QPoint pos = event->pos();
	if (event->button() == Qt::LeftButton)
	{
		qDebug() << pos << endl;
		if ((pos.x() >= 104) && (pos.x() <= 118) && (pos.y() >= 5) && (pos.y() <= 22))
		{
			qDebug() << "1" << i << endl;
			createSpell[i] = 1;
			++i;
		}
		if ((pos.x() >= 203) && (pos.x() <= 218) && (pos.y() >= 102) && (pos.y() <= 118))
		{
			qDebug() << "2" << endl;
			createSpell[i] = 2;
			i++;
		}
		if ((pos.x() >= 104) && (pos.x() <= 118) && (pos.y() >= 201) && (pos.y() <= 218))
		{
			qDebug() << "3" << endl;
		}
		if ((pos.x() >= 2) && (pos.x() <= 16) && (pos.y() >= 102) && (pos.y() <= 117))
		{
			qDebug() << "4" << endl;
		}
		if ((pos.x() >= 102) && (pos.x() <= 116) && (pos.y() >= 101) && (pos.y() <= 117))
		{
			//qDebug() << "5" << endl;
			for (int l = 0; l < i; l++)
			{

				qDebug() << "mass: " << createSpell[l];
			}
		}
	}
	
}


