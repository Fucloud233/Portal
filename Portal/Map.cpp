#include "Map.h"

#include "GraphicsBlockItem.h"

#include <QBrush>
#include <QPen>

Map::Map() {

}

void Map::initial(int blockSize) {
	this->blockSize = blockSize;

	int size = 10;
	data = Matrix<Block* >(10, 10, NULL);
	items = Matrix<QGraphicsItem*>(10, 10, NULL);

	for (int i = data.bound(Direct::TOP); i != data.bound(Direct::BOTTOM); i++) {
		for (int j = data.bound(Direct::LEFT); j != data.bound(Direct::RIGHT); j++) {
			// 创建item对象
			QGraphicsRectItem* item = new QGraphicsRectItem();
			item->setRect(j * blockSize, i * blockSize, blockSize, blockSize);
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

bool Map::modify(const QPoint& point, Block* block) {
	return modify(point.x(), point.y(), block);
}

bool Map::modify(int x, int y, Block* block) {
	if (!data.checkIndex(y, x)) {
		return false;
	}    
	
	// 创建对应编号
	GraphicsBlockItem* item = new GraphicsBlockItem(QPoint(x, y), block->BlockImg(), this);
	item->setFlag(QGraphicsItem::ItemIsMovable);

	delete items[y][x];
	items[y][x] = item;
	data[y][x] = block;

	return true;
}

int Map::BlockSize() const {
	return blockSize;
}

QGraphicsItem* Map::getItem(int x, int y) {
	return items[y][x];
}

QGraphicsItem* Map::getItem(const QPoint& point) {
	return items[point.y()][point.x()];
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

bool Map::checkPos(const QPoint& p) const {
	return data.checkIndex(p.y(), p.x());
}

bool Map::translatePos(QPoint& point) const {
	point.setX(point.x() / blockSize);
	point.setY(point.y() / blockSize);

	return this->checkPos(point);
}