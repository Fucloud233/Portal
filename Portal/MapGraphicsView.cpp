#include "MapGraphicsView.h"

MapGraphicsView::MapGraphicsView(QWidget* parent) :
	QGraphicsView(parent) {

}

void MapGraphicsView::initialScene() {
	const QList<BlockGraphicsItem*>& items = map->getItems();

	for (BlockGraphicsItem* item : items) {
		scene->addItem(item);
	}
}