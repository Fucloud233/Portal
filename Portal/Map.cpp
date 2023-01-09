#include "Map.h"

#include <QBrush>
#include <QPen>

Map::Map() {

}

void Map::initial(int BlockSize) {
	this->BlockSize = BlockSize;

	int size = 10;
	data = Matrix<Block* >(10, 10, NULL);
	items = Matrix<QGraphicsItem*>(10, 10, NULL);

	for (int i = data.bound(Direct::TOP); i != data.bound(Direct::BOTTOM); i++) {
		for (int j = data.bound(Direct::LEFT); j != data.bound(Direct::RIGHT); j++) {
			// 创建item对象
			QGraphicsRectItem* item = new QGraphicsRectItem();
			item->setRect(i * BlockSize, j * BlockSize, BlockSize, BlockSize);
			item->setPen(QPen(Qt::white, 1.5));

			//item->setBrush(Qt::gray);
			//item->setFlag(QGraphicsItem::ItemIsMovable);

			// 将对象放入存储
			items[i][j] = item;
		}
	}
}

Map::~Map() {

}

bool Map::modify(int x, int y, Block* block) {
	if (!data.checkIndex(y, x)) {
		return false;
	}

	data[y][x] = block;

	delete items[y][x];
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
	item->setPos(x * BlockSize, y * BlockSize);
	item->setPixmap(block->BlockImg());
	item->setScale(BlockSize / block->BlockImg().width());
	items[y][x] = item;

	return true;
}


QGraphicsItem* Map::getItem(int x, int y) {
	return items[y][x];
}

QList<QGraphicsItem*> Map::getItems() {
	QList<QGraphicsItem*> itemsList;

	for (int i = items.bound(Direct::TOP); i != items.bound(Direct::BOTTOM); i++) {
		for (int j = items.bound(Direct::LEFT); j != items.bound(Direct::RIGHT); j++) {
			// 创建item对象
			itemsList.append(items[i][j]);
		}
	}
	return itemsList;
}

bool Map::checkPos(int x, int y) const {
	return data.checkIndex(y, x);
}