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

	// 初始化变量
	int width = 10, height = 10;
	data = Matrix<Block* >(width, height, NULL);
	statuses = Matrix<BlockStatus>(width, height, BlockStatus());
	items = Matrix<BlockGraphicsItem*>(width, height, NULL);

	for (int i = data.bound(Direct::TOP); i != data.bound(Direct::BOTTOM); i++) {
		for (int j = data.bound(Direct::LEFT); j != data.bound(Direct::RIGHT); j++) {
			// 创建item对象
			items[i][j] = new BlockGraphicsItem(j, i, this);
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
	BlockGraphicsItem* item = new BlockGraphicsItem(x, y, block->BlockImg(), this);
	item->setFlag(QGraphicsItem::ItemIsMovable);

	delete items[y][x];
	items[y][x] = item;
	data[y][x] = block;
	statuses[y][x].initial(*block);

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
	statuses.swap(s_y, s_x, t_y, t_x);

	return true;
}

int Map::BlockSize() const {
	return blockSize;
}

bool Map::hasSelected() const {
	return !selected_block_index.isNull();
}

void Map::setSelectedPos(const QPoint& point) {
	this->selected_block_index = point;
}

QPoint Map::getSelectedPos() const {
	return selected_block_index;
}

Block* Map::getSelectedBlock() const {
	return getBlock(selected_block_index);
}

BlockStatus* Map::SelectedBlockStatus() const {
	return &statuses[selected_block_index.y()][selected_block_index.x()];
}

Block* Map::getBlock(const QPoint& point) const {
	return data[point.y()][point.x()];
}

Block* Map::getBlock(int x, int y) const {
	return data[y][x];
}

BlockGraphicsItem* Map::getItem(int x, int y) const{
	return items[y][x];
}

BlockGraphicsItem* Map::getItem(const QPoint& point) const {
	return items[point.y()][point.x()];
}

QList<BlockGraphicsItem*> Map::getItems() {
	QList<BlockGraphicsItem*> itemsList;

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