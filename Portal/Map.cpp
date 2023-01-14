#include "Map.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Map::Map(int blockSize) {
	this->blockSize = blockSize;
	height = width = 0;
}

Map::Map(int width, int height, int blockSize) {
	initial(width, height, blockSize);
}

Map::~Map() {
	QList<BlockGraphicsItem*> items;
	for (BlockGraphicsItem* item : items)
		delete item;
}

void Map::initial(int width, int height, int blockSize) {
	// 初始化变量
	this->blockSize = blockSize;
	this->width = width; this->height = height;

	// 对存储变量进行初始化
	blocks = Matrix<BlockStatus*>(width, height, NULL);
	items = Matrix<BlockGraphicsItem*>(width, height, NULL);
}

bool Map::modify(const QPoint& point, BlockStatus* status) {
	return modify(point.x(), point.y(), status);
}

bool Map::modify(int x, int y,  BlockStatus* status) {
	if (!blocks.checkIndex(y, x)) {
		return false;
	}

	if (blocks[y][x]) delete blocks[y][x];
	if (items[y][x]) delete items[y][x];

	blocks[y][x] = status;
	items[y][x] = new BlockGraphicsItem(x, y, status->BlockImg(), this);

	return true;
}

int Map::BlockSize() const {
	return blockSize;
}

BlockStatus* Map::getBlockStatus(const QPoint& point) const {
	return blocks[point.y()][point.x()];
}

BlockStatus* Map::getBlockStatus(int x, int y) const {
	return blocks[y][x];
}

BlockGraphicsItem* Map::getItem(int x, int y) const {
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
	return blocks.checkIndex(y, x);
}

bool Map::checkPos(const QPoint& p) const {
	return blocks.checkIndex(p.y(), p.x());
}

bool Map::checkX(int x) const {
	return blocks.checkIndex(blocks.bound(Direct::TOP), x);
}
bool Map::checkY(int y) const {
	return blocks.checkIndex(y, blocks.bound(Direct::LEFT));
}

bool Map::isNULL(const QPoint& point) const {
	return blocks[point.y()][point.x()]->isNULL();
}

bool Map::translatePos(QPoint& point) const{
	point.setX(point.x() / blockSize);
	point.setY(point.y() / blockSize);

	return this->checkPos(point);
}

void Map::write(QJsonObject& json) {
	// 将Block信息转换为Json数组
	QJsonArray jsonArray;

	for (int i = blocks.bound(Direct::TOP); i != blocks.bound(Direct::BOTTOM); i++) {
		for (int j = blocks.bound(Direct::LEFT); j != blocks.bound(Direct::RIGHT); j++) {
			// 创建item对象
			if (!blocks[i][j]) {
				// 存 the Block of Code and Status
				QJsonObject statusJson;
				statusJson["x"] = j; statusJson["y"] = i;
				blocks[i][j]->write(statusJson);

				jsonArray.append(statusJson);
			}
		}
	}

	// 将整个数组作为一个Json存储
	json["Blocks"] = jsonArray;
	json["Width"] = width;
	json["Height"] = height;
}

void Map::read(const QJsonObject& json) {
	QJsonArray jsonArray = json["Blocks"].toArray();

	for (int i = 0; i < jsonArray.size(); i++) {
		QJsonObject statusJson = jsonArray[i].toObject();

		// 从Json中加载信息
		int x = statusJson["x"].toInt(), y = statusJson["y"].toInt();
		int code = statusJson["code"].toInt();
		BlockStatus* status =  new BlockStatus; 
		status->read(statusJson);

		// 根据读取内容进行修改
		modify(x, y, status);
	}
}