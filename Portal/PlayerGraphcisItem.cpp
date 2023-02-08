#include "PlayerGraphicsItem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>

PlayerGraphicsItem::PlayerGraphicsItem() {
	R = blockSize / 4;
	copy_player = NULL;
}

PlayerGraphicsItem::PlayerGraphicsItem(const QPoint& pos, MapGame* map) {
	parentMap = map;
	setPos(pos * blockSize);
	setZValue(GraphicsItem::ON);
	R = blockSize / 4;
	
	// 用于生成传送的假象a
	copy_player = new PlayerGraphicsItem();
	copy_player->setZValue(GraphicsItem::ON);
	copy_player->setVisible(false);
	//scene()->addItem(copy_player);
	//enter_flag = false;
}

void PlayerGraphicsItem::moveX(float step) {
	int x = QGraphicsItem::x();
	QGraphicsItem::setX(step + x);
	if (!checkcolliding()) 
		QGraphicsItem::setX(x);
}

void PlayerGraphicsItem::moveY(float step) {
	int y = QGraphicsItem::y();
	QGraphicsItem::setY(step + y);
	if (!checkcolliding())
		QGraphicsItem::setY(y);
}

bool PlayerGraphicsItem::checkcolliding() {
	copy_player->setVisible(false);

	QList<QGraphicsItem *> items = this->collidingItems(Qt::IntersectsItemShape);
	for (int i = 0; i < items.size();i++) {
		BlockGameGraphicsItem* item = qgraphicsitem_cast<BlockGameGraphicsItem*>(items[i]);
		if (item->type() == ElemType::UNPASSABLE) {
			return false;
		}

		if (item->type() == BlockGameGraphicsItem::RED_DOOR|| item->type() == BlockGameGraphicsItem::BLUE_DOOR) {
			if (!parentMap->canTeleport())
				return false;

			bool isRed = item->type() == BlockGameGraphicsItem::RED_DOOR;
			// 当在传送方块旁边时 传送
			if (parentMap->canEnter(item->Index(), item->SideAbout(this), isRed)) {
				copy_player->setVisible(true);

				Block::Side side = isRed ? parentMap->RedDoorSide() : parentMap->BlueDoorSide();
				drawCopyPlayer(item->SidePos(side), isRed);

				if (collidesWithItem(item, Qt::ContainsItemShape)) {
					setPos(copy_player->pos());
					copy_player->setVisible(false);
				}
			}
			else 
				return false;
		}
	}

	return true;
}

void PlayerGraphicsItem::drawCopyPlayer(const QPoint& pos, bool isRed) {
	QPoint outPos = isRed ? parentMap->BlueDoorPos() : parentMap->RedDoorPos();
	Block::Side inSide = isRed ? parentMap->RedDoorSide() : parentMap->BlueDoorSide();
	Block::Side outSide = isRed ? parentMap->BlueDoorSide() : parentMap->RedDoorSide();

	QPoint diffPos = (scenePos() - pos * blockSize).toPoint();
	translatePos(diffPos, inSide, outSide);

	copy_player->setPos(outPos * blockSize + diffPos);
}

void PlayerGraphicsItem::translatePos(QPoint& pos, Block::Side s_side, Block::Side t_side) {
	int diff = t_side - s_side;

	// 0
	if (diff == 0)
		pos = QPoint(-pos.x(), -pos.y());
	// 90
	else if (diff == 1 || diff == -3)
		pos = QPoint(pos.y(), -pos.x());
	// 180
	else if (diff == 2 || diff == -2) 
		return;
	// 270
	else if (diff == 3 || diff == -1)
		pos = QPoint(-pos.y(), pos.x());
}

QRectF PlayerGraphicsItem::boundingRect() const {
	return QRectF(-R, -R, 2 * R, 2 * R);
}

QPainterPath PlayerGraphicsItem::shape() const {
	QPainterPath path;
	// 注意有一圈描边
	path.addEllipse(-R, -R, 2 * R, 2 * R);
	
	//qreal x = (R * 1.2) * qCos(angle);
	//qreal y = (R * 1.2) * qSin(angle);
	//path.addEllipse(QPointF(x, y), 0.3 * R, 0.3 * R);

	return path;
}

int PlayerGraphicsItem::type() const {
	return ElemType::PLAYER;
}

void PlayerGraphicsItem::setDirect(qreal direct) {
	this->angle = direct;
}


qreal PlayerGraphicsItem::Direct() const {
	return angle;
}

PlayerGraphicsItem* PlayerGraphicsItem::Copy() {
	return copy_player;
}

void PlayerGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

	painter->setPen(QPen(Qt::gray, 1.5));
	painter->setBrush(Qt::white);
	painter->drawEllipse(QPoint(0, 0), R, R);

	qreal x = (R * 1.2) * qCos(angle);
	qreal y = (R * 1.2) * qSin(angle);

	painter->drawEllipse(QPointF(x, y), 0.3 * R, 0.3 * R);

	//painter->setPen(QPen(Qt::blue, 1.5));
	//painter->drawRect(0, 0, blockSize, blockSize);
}
