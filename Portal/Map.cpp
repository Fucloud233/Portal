#include "Map.h"

#include "BlockInfoOperator.h"

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
}

Map::~Map() {

}

void Map::initial(int width, int height) {
	// 初始化变量
	this->width = width; this->height = height;
	
	//data = Matrix<Block* >(width, height, NULL);
	statuses = Matrix<BlockStatus>(width, height, BlockStatus());
	items = Matrix<BlockGraphicsItem*>(width, height, NULL);

	// 每个Item 由于所在坐标不同 需要单独设置
	for (int i = items.bound(Direct::TOP); i != items.bound(Direct::BOTTOM); i++) {
		for (int j = items.bound(Direct::LEFT); j != items.bound(Direct::RIGHT); j++) {
			// 创建item对象
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
	
	// 修改对应的Item
	BlockGraphicsItem* item = new BlockGraphicsItem(x, y, BlockInfoOperator::value(blockCode)->BlockImg(), this);
	item->setFlag(QGraphicsItem::ItemIsMovable);

	delete items[y][x];
	items[y][x] = item;
	//data[y][x] = block;

	if (status)
		statuses[y][x] = *status;
	else
		// 当没有特定的status传入时 利用默认构造函数传递
		statuses[y][x] = BlockStatus(blockCode);

	return true;
}

bool Map::swap(const QPoint& source, const QPoint& target) {
	return this->swap(source.x(), source.y(), target.x(), target.y());
}

bool Map::swap(int s_x, int s_y, int t_x, int t_y) {
	// 判断Pos是否越界
	if (!statuses.checkIndex(s_y, s_x) || !statuses.checkIndex(t_y, t_x)) {
		return false;
	}
	
	// 判断移动是否满足情况
	//if (data[s_y][s_x] == NULL) {
	//	return false;
	//}

	// 这里调用的是基类的函数
	items[s_y][s_x]->setPos(t_x, t_y);
	items[t_y][t_x]->setPos(s_x, s_y);

	items.swap(s_y, s_x, t_y, t_x);
	//data.swap(s_y, s_x, t_y, t_x);
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

BlockStatus* Map::SelectedBlockStatus() const {
	return &statuses[selected_block_index.y()][selected_block_index.x()];
}

BlockStatus* Map::getBlockStatus(const QPoint& point) const {
	return &statuses[point.y()][point.x()];
}

BlockStatus* Map::getBlockStatus(int x, int y) const {
	return &statuses[y][x];
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
	return statuses.checkIndex(y, x);
}

bool Map::checkPos(const QPoint& p) const {
	return statuses.checkIndex(p.y(), p.x());
}

bool  Map::checkX(int x) const {
	return statuses.checkIndex(statuses.bound(Direct::TOP), x);
}
bool  Map::checkY(int y) const {
	return statuses.checkIndex(y, statuses.bound(Direct::LEFT));
}

bool Map::isNULL(const QPoint& point) const {
	return statuses[point.y()][point.x()].isNULL();
}

bool Map::translatePos(QPoint& point) const {
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
			if (!statuses[i][j].isNULL()) {
				// 存 the Block of Code and Status
				QJsonObject statusJson;
				statusJson["x"] = j;
				statusJson["y"] = i;
				statuses[i][j].write(statusJson);
				
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
	
	for (int i = 0; i < jsonArray.size();i++) {
		QJsonObject statusJson = jsonArray[i].toObject();

		// 从Json中加载信息
		int x = statusJson["x"].toInt(), y = statusJson["y"].toInt();
		int code = statusJson["code"].toInt();
		//Block* block = BlockInfoOperator::value(statusJson["code"].toInt());
		BlockStatus status; status.read(statusJson);

		modify(x, y, code, &status);
	}
}