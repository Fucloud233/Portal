#include "MapGame.h"
#include "BlockGameGraphicsItem.h"

MapGame::MapGame():
	Map() {

	current_pos = QPoint(0, 0);
	// 规定 可移动范围都是正数
	red_pos = QPoint(-1, -1);
	blue_pos = QPoint(-1, -1);
}

bool MapGame::checkPoint(const QPoint& pos) const {
	return pos != QPoint(-1, -1);
}

void MapGame::openDoor(QPoint pos, Block::Side side, bool isRed) {
	if (!checkPos(pos) || side ==Block::INVALID || !blocks[pos.y()][pos.x()]->canOpen()) {
		return;
	}

	// 判断所朝面是否为空
	//QPoint nearPos = pos;
	//switch (side) {
	//case Block::UP:
	//	nearPos += QPoint(0, -1);
	//	break;
	//case Block::DOWN:
	//	nearPos += QPoint(0, 1);
	//	break;
	//case Block::LEFT:
	//	nearPos += QPoint(-1, 0);
	//	break;
	//case Block::RIGHT:
	//	nearPos += QPoint(1, 0);
	//	break;
	//}

	//if (Status(nearPos)->getBlockType() != Block::FLOOR)
	//	return;
	
	// 当发生覆盖的时候要进行处理
	if (isRed && pos == blue_pos && side == blue_side) 
		blue_pos = QPoint(-1, -1);
	else if (!isRed && pos == red_pos && side == red_side) 
		red_pos = QPoint(-1, -1);

	// 根据颜色判断要修改的坐标
	QPoint& blockPos = isRed ? red_pos : blue_pos;
	Block::Side& blockSide = isRed ? red_side : blue_side;

	// 坐标有效+能够开门->开门
	blockPos = pos;
	blockSide = side;
}

bool MapGame::canTeleport() {
	return checkPoint(red_pos)&&checkPoint(blue_pos);
}

bool MapGame::canEnter(const QPoint& pos, Block::Side side, bool isRed) {
	if (isRed) {
		return pos == RedDoorPos() && (side == RedDoorSide() || side == Block::CENTER);
	}
	else
		return pos == BlueDoorPos() && (side == BlueDoorSide() || side == Block::CENTER);
}

QPoint MapGame::RedDoorPos() const {
	return red_pos;
}

QPoint MapGame::BlueDoorPos() const {
	return blue_pos;
}

Block::Side MapGame::RedDoorSide() const {
	return red_side;
}

Block::Side MapGame::BlueDoorSide() const {
	return blue_side;
}

void MapGame::read(const QJsonObject& json) {
	Map::read(json);

	current_pos = spawn_pos;
	//qDebug() << current_pos.x() << current_pos.y();
}

bool MapGame::modify(int x, int y, BlockStatus* status) {
	if (!blocks.checkIndex(y, x)) {
		return false;
	}

	if (blocks[y][x]) delete blocks[y][x];
	if (items[y][x]) delete items[y][x];

	blocks[y][x] = status;
	items[y][x] = new BlockGameGraphicsItem(x, y, status->BlockImg(), this);

	return true;
}