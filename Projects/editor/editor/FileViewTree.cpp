#include "FileViewTree.h"

FileViewTree::FileViewTree(QWidget* parent) : QTreeWidget(parent)
{
	init();
}
void FileViewTree::init() {
	setMouseTracking(1);

	initMenu();

	//setSelectionMode(QTreeWidget::MultiSelection);

	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(slotCustomContextMenu(const QPoint&)));
	
	setHeaderLabel("Files:");
}
void FileViewTree::initMenu() {
	contextMenu = new QMenu(this);

	actRemove = new QAction("Remove", this);
	actRemove->setIcon(QPixmap("Resources/Remove.png"));

	contextMenu->addAction(actRemove);

	connect(actRemove, SIGNAL(triggered()), SLOT(slotRemoveItem()));
}
void FileViewTree::addItem(QString file) {
	QTreeWidgetItem* item;

	item = new QTreeWidgetItem(this);

	QString name = file.split("/").back();

	item->setText(0, name);
	item->setIcon(0, QPixmap("Resources/File.png"));

	item->setToolTip(0, file);
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	this->addTopLevelItem(item);

}
void FileViewTree::addItems(QStringList files) {
	foreach(QString file, files)
		addItem(file);

}
void FileViewTree::removeItem(QString file) {
	for (int i = 0; i < this->topLevelItemCount(); i++) {
		QTreeWidgetItem* item = this->topLevelItem(i);
		QString text = item->toolTip(0);
		if (text == file) {
			emit signalRemoveFile(text);
			//this->items.removeOne(item);
			delete item;
			break;
		}
	}

}
void FileViewTree::removeItem(int index) {
	this->items.removeAt(index);

}
void FileViewTree::slotCustomContextMenu(const QPoint& p) {
	contextMenu->popup(this->viewport()->mapToGlobal(p));
}
void FileViewTree::slotRemoveItem() {
	foreach(QTreeWidgetItem* item, this->selectedItems())
		removeItem(item->toolTip(0));

}
void FileViewTree::slotItemNameChanged(QTreeWidgetItem* item, int col) {

}

void FileViewTree::mouseDoubleClickEvent(QMouseEvent * e)
{
	QTreeWidgetItem* selectedItem = this->currentItem();
	QString name = selectedItem->text(0);
	emit itemDoubleClicked(selectedItem);
}
