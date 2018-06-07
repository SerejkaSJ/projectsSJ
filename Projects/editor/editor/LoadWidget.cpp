#include "LoadWidget.h"

LoadingWidget::LoadingWidget(QWidget* parent) : QWidget(parent)
{
	init();

	setWindowTitle("Loading");
}
void LoadingWidget::init() {
	label = new QLabel("Are you really think the loading is real? Please, close it... NOW!", this);
	label->setStyleSheet("QLabel { qproperty-alignment: AlignCenter;}");

	movie = new QMovie("Resources/Loading.gif");
	movie->setScaledSize(QSize(300, 300));

	movieLabel = new QLabel(this);
	movieLabel->setMovie(movie);
	movieLabel->setAlignment(Qt::AlignCenter);
	movieLabel->setStyleSheet("QLabel { background : rgb( 255, 255, 255); }");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(movieLabel, Qt::AlignCenter);
	layout->addWidget(label);
	layout->setMargin(0);
	layout->setSpacing(0);

	this->setLayout(layout);

	this->resize(QSize(350, 350));

	this->setContentsMargins(0, 0, 0, 0);
}

void LoadingWidget::start() {
	show();

	movie->start();
}