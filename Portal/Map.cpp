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

Map::~Map() {

}

void Map::initial(int width, int height) {
	// 初始化变量
	this->width = width; this->height = height;

	// [修改] 将statuses 修改为指针
	statuses = Matrix<BlockStatus*>(width, height, NULL);
	items = Matrix<BlockGraphicsItem*>(width, height, NULL);

	// 每个Item 由于所在坐标不同 需要单独设置
	for (int i = items.bound(Direct::TOP); i != items.bound(Direct::BOTTOM); i++) {
		for (int j = items.bound(Direct::LEFT); j != items.bound(Direct::RIGHT); j++) {
			// 创建item对象
			statuses[i][j] = new BlockStatus();
			items[i][j] = new BlockGraphicsItem(j, i, this);
		}
	}
}

bool Map::modify(const QPoint& point, int blockCode, BlockStatus* status) {
	return modify(point.x(), point.y(), blockCode, status);
}

bool Map::modify(int x, int y, int blockCode, BlockStatus* status) {
	if (!statuses.checkIndex(y, x)) {
		return false;
	}

	// [修改] item的修改的方式: delete + add -> set 
	items[y][x]->setImg(BlockInfoOperator::value(blockCode)->BlockImg());

	// 当没有特定的status传入时 利用默认构造函数传递
	if (status) {
		delete statuses[y][x];
		statuses[y][x] = status;
	}
	else
		statuses[y][x]->setBlock(blockCode);

	return true;
}


int Map::BlockSize() const {
	return blockSize;
}

BlockStatus* Map::getBlockStatus(const QPoint& point) const {
	return statuses[point.y()][point.x()];
}

BlockStatus* Map::getBlockStatus(int x, int y) const {
	return statuses[y][x];
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
	return statuses.checkIndex(y, x);
}

bool Map::checkPos(const QPoint& p) const {
	return statuses.checkIndex(p.y(), p.x());
}

bool Map::checkX(int x) const {
	return statuses.checkIndex(statuses.bound(Direct::TOP), x);
}
bool Map::checkY(int y) const {
	return statuses.checkIndex(y, statuses.bound(Direct::LEFT));
}

bool Map::isNULL(const QPoint& point) const {
	return statuses[point.y()][point.x()]->isNULL();
}

bool Map::translatePos(QPoint& point) const{
	point.setX(point.x() / blockSize);
	point.setY(point.y() / blockSize);

	return this->checkPos(point);
}

void Map::write(QJsonObject& json) {
	// 将Block信息转换为Json数组
	QJsonArray jsonArray;

	for (int i = statuses.bound(Direct::TOP); i != statuses.bound(Direct::BOTTOM); i++) {
		for (int j = statuses.bound(Direct::LEFT); j != statuses.bound(Direct::RIGHT); j++) {
			// 创建item对象
			if (!statuses[i][j]) {
				// 存 the Block of Code and Status
				QJsonObject statusJson;
				statusJson["x"] = j;
				statusJson["y"] = i;
				statuses[i][j]->write(statusJson);

				jsonArray.append(statusJson);
			}
		}
	}

	// 将整个数组作为一个Json存储
	json["Blocks"] = jsonArray;
	json["Width"] = width;
	json["Height"] = height;
}

void Map::read(QJsonObject& json) {
	initial(json["Width"].toInt(), json["Height"].toInt());

	QJsonArray jsonArray = json["Blocks"].toArray();

	for (int i = 0; i < jsonArray.size(); i++) {
		QJsonObject statusJson = jsonArray[i].toObject();

		// 从Json中加载信息
		int x = statusJson["x"].toInt(), y = statusJson["y"].toInt();
		int code = statusJson["code"].toInt();
		//Block* block = BlockInfoOperator::value(statusJson["code"].toInt());
		BlockStatus* status =  new BlockStatus; 
		status->read(statusJson);

		// 根据读取内容进行修改
		modify(x, y, code, status);
	}
}