#include "BlockGameGraphicsItem.h"

BlockGameGraphicsItem::BlockGameGraphicsItem(MapGame* map) :
	BlockGraphicsItem(map) {
}

BlockGameGraphicsItem::BlockGameGraphicsItem(const QPoint& index, const QPixmap& img, Map* map) :
	BlockGraphicsItem(map) {

	initial(index, img, map);
}

BlockGameGraphicsItem::BlockGameGraphicsItem(int x, int y, const QPixmap& img, Map* map) :
	BlockGameGraphicsItem(QPoint(x, y), img, map) {
}

BlockGameGraphicsItem::BlockGameGraphicsItem(const QPoint& index, Map* map) :
	BlockGameGraphicsItem(index, QPixmap(), map) {
}

BlockGameGraphicsItem::BlockGameGraphicsItem(int x, int y, Map* map) :
	BlockGameGraphicsItem(QPoint(x, y), QPixmap(), map) {
}

int BlockGameGraphicsItem::type() const {
	if (index == ((MapGame*)parentMap)->RedDoorPos())
		return RED_DOOR;
	else if(index == ((MapGame*)parentMap)->BlueDoorPos())
		return BLUE_DOOR;
	else
		return BlockGraphicsItem::type();
}

void BlockGameGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

	BlockGraphicsItem::paint(painter, option, widget);

	painter->setPen(Qt::NoPen);

	QPen pen;
	pen.setWidth(2);

	setHeight(origin_height);

	if (index == ((MapGame*)parentMap)->RedDoorPos()) {
		pen.setColor(Qt::red);
		painter->setPen(pen);
		setHeight(SELECTED);

		paintDoor(painter, ((MapGame*)parentMap)->RedDoorSide());
	}

	if (index == ((MapGame*)parentMap)->BlueDoorPos()) {
		pen.setColor(Qt::blue);
		painter->setPen(pen);
		setHeight(SELECTED);

		paintDoor(painter, ((MapGame*)parentMap)->BlueDoorSide());
	}
}

void BlockGameGraphicsItem::paintDoor(QPainter* painter, Block::Side side) {
	QPointF start_point, end_point;
	int doorR = blockSize / 2 / 1.2;

	switch (side) {
	case Block::UP:
		start_point = QPointF(-doorR, -blockSize/2);
		end_point = QPointF(doorR, -blockSize/2);
		break;
	case Block::DOWN:
		start_point = QPointF(-doorR, +blockSize / 2);
		end_point = QPointF(doorR, +blockSize / 2);
		break;
	case Block::LEFT:
		start_point = QPointF(-blockSize / 2, -doorR);
		end_point = QPointF(-blockSize / 2, doorR);
		break;
	case Block::RIGHT:
		start_point = QPointF(+blockSize / 2, -doorR);
		end_point = QPointF(+blockSize / 2, doorR);
		break;
	}

	painter->drawLine(start_point, end_point);
}