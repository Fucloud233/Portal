#include "Map.h"

#include <QBrush>
#include <QPen>

Map::Map() {

}

void Map::initial() {
	int size = 10;
	data = Matrix<Block>(size, size, Block());
}

QList<QGraphicsItem*> Map::getItems(int BlockSize) {
	QList<QGraphicsItem*> items;
	for (int i = data.bound(Direct::TOP); i != data.bound(Direct::BOTTOM); i++) {
		for (int j = data.bound(Direct::LEFT); j != data.bound(Direct::RIGHT); j++) {
			QGraphicsRectItem* item = new QGraphicsRectItem();
			item->setRect(i*BlockSize, j*BlockSize,BlockSize, BlockSize);
			//item->setBrush(Qt::gray);
			item->setPen(QPen(Qt::white, 1.5));
			//item->setFlag(QGraphicsItem::ItemIsMovable);
			items.push_back(item);
		}
	}
	
	return items;
}

bool Map::checkPos(int x, int y) const {
	return data.checkIndex(y, x);
}