#include "PlayerGraphicsItem.h"

#include <QPainter>
#include <QBrush>

PlayerGraphicsItem::PlayerGraphicsItem(const QPoint& pos, int BlockSize):
	GraphicsItem(BlockSize) {
	setPos(pos);
	R = blockSize / 3;
}

void PlayerGraphicsItem::moveX(float step) {
	int x = QGraphicsItem::x();
	QGraphicsItem::setX(step + x);
	if (checkcolliding()) 
		index.setX(x / blockSize);
	else 
		QGraphicsItem::setX(x);
}

void PlayerGraphicsItem::moveY(float step) {
	int y = QGraphicsItem::y();
	QGraphicsItem::setY(step + y);
	if (checkcolliding())
		index.setY(y / blockSize);
	else
		QGraphicsItem::setY(y);
}

bool PlayerGraphicsItem::checkcolliding() {

	QList<QGraphicsItem *> items = this->collidingItems(Qt::IntersectsItemShape);
	for (int i = 0; i < items.size();i++) {
		GraphicsItem* item = qgraphicsitem_cast<GraphicsItem*>(items[i]);
		if (!item->isAccessible()) {
			return false;
		}
	}
	
	return true;
}

bool PlayerGraphicsItem::isAccessible() const {
	return false;
}

QRectF PlayerGraphicsItem::boundingRect() const {
	return QRectF(0, 0, blockSize, blockSize);
}

QPainterPath PlayerGraphicsItem::shape() const {
	QPainterPath path;
	// 注意有一圈描边
	path.addEllipse(QPoint(blockSize / 2, blockSize / 2), R + 0.5, R + 0.5);
	return path;
}

void PlayerGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

	painter->setPen(QPen(Qt::gray, 1.5));
	painter->setBrush(Qt::white);
	painter->drawEllipse(QPoint(blockSize / 2, blockSize / 2), R, R);

	//painter->setPen(QPen(Qt::blue, 1.5));
	//painter->drawRect(0, 0, blockSize, blockSize);
}
