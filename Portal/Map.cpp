#include "Map.h"

#include <QBrush>
#include <QPen>
#include <QPainter>

Map::Map() {
	blockSize = 0;
}

Map::~Map() {

}

void Map::initial(int blockSize) {
	this->blockSize = blockSize;

	int size = 10;
	data = Matrix<Block* >(10, 10, NULL);
	items = Matrix<GraphicsBlockItem*>(10, 10, NULL);

	QPixmap orignImg(32, 32);
	orignImg.fill(Qt::transparent);

	// 绘制初始化图形
	QPainter painter(&orignImg);
	painter.setPen(QPen(Qt::gray, 1.5));
	painter.drawRect(0, 0, blockSize , blockSize);

	for (int i = data.bound(Direct::TOP); i != data.bound(Direct::BOTTOM); i++) {
		for (int j = data.bound(Direct::LEFT); j != data.bound(Direct::RIGHT); j++) {
			// 创建item对象
			items[i][j] = new GraphicsBlockItem(j, i, orignImg, this);
		}
	}
}

bool Map::modify(const QPoint& point, Block* block) {
	return modify(point.x(), point.y(), block);
}

bool Map::modify(int x, int y, Block* block) {
	if (!data.checkIndex(y, x)) {
		return false;
	}    
	
	// 创建对应编号
	GraphicsBlockItem* item = new GraphicsBlockItem(x, y, block->BlockImg(), this);
	item->setFlag(QGraphicsItem::ItemIsMovable);

	delete items[y][x];
	items[y][x] = item;
	data[y][x] = block;

	return true;
}

bool Map::swap(const QPoint& source, const QPoint& target) {
	return this->swap(source.x(), source.y(), target.x(), target.y());
}

bool Map::swap(int s_x, int s_y, int t_x, int t_y) {
	// 判断Pos是否越界
	if (!data.checkIndex(s_y, s_x) || !data.checkIndex(t_y, t_x)) {
		return false;
	}
	
	// 判断移动是否满足情况
	if (data[s_y][s_x] == NULL) {
		return false;
	}

	// 这里调用的是基类的函数
	items[s_y][s_x]->setPos(t_x, t_y);
	items[t_y][t_x]->setPos(s_x, s_y);
	items.swap(s_y, s_x, t_y, t_x);

	data.swap(s_y, s_x, t_y, t_x);

	return true;
}

int Map::BlockSize() const {
	return blockSize;
}

GraphicsBlockItem* Map::getItem(int x, int y) const{
	return items[y][x];
}

GraphicsBlockItem* Map::getItem(const QPoint& point) const {
	return items[point.y()][point.x()];
}

QList<GraphicsBlockItem*> Map::getItems() {
	QList<GraphicsBlockItem*> itemsList;

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

bool  Map::checkX(int x) const {
	return data.checkIndex(data.bound(Direct::TOP), x);
}
bool  Map::checkY(int y) const {
	return data.checkIndex(y, data.bound(Direct::LEFT));
}


bool Map::isNULL(const QPoint& point) const {
	return data[point.y()][point.x()] == NULL;
}

bool Map::translatePos(QPoint& point) const {
	point.setX(point.x() / blockSize);
	point.setY(point.y() / blockSize);

	return this->checkPos(point);
}