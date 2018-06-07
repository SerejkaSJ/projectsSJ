
#include "ListElement.h"

ListElement::ListElement(QWidget* parent) : QTreeWidget(parent)
{
	init();

}
void ListElement::init() {
	setMouseTracking(1);

	setSelectionMode(QTreeWidget::MultiSelection);

	//connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(slotCustomContextMenu(const QPoint&)));
	
	setHeaderLabel("Files:");
}

void ListElement::addItem(QString file, vector<Gate*> gates) {
//void ListElement::addItem(QString file) {
	QTreeWidgetItem* item = new QTreeWidgetItem(this);
	QString name = file.split("/").back();

	item->setText(0, name);
	item->setIcon(0, QPixmap("Resources/scheme.png"));
	item->setToolTip(0, file);
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	this->addTopLevelItem(item);
	for (int i = 0; i < gates.size(); i++) {
		QTreeWidgetItem *item1 = new QTreeWidgetItem(item);
		item1->setText(0, gates[i]->name.c_str());
		for (int j = 0; j < gates[i]->CompositionGate.size(); j++) {
			QTreeWidgetItem *item2 = new QTreeWidgetItem(item1);
			item2->setText(0, gates[i]->CompositionGate[j]->name.c_str());
		}
	}
}