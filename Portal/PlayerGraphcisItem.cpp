#include "PlayerGraphicsItem.h"

#include <QPainter>
#include <QBrush>

PlayerGraphicsItem::PlayerGraphicsItem(const QPoint& pos, int BlockSize):
	GraphicsItem(BlockSize) {
	setPos(pos * blockSize);
	R = blockSize / 3;
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
	QList<QGraphicsItem *> items = this->collidingItems(Qt::IntersectsItemShape);
	for (int i = 0; i < items.size();i++) {
		GraphicsItem* item = qgraphicsitem_cast<GraphicsItem*>(items[i]);
		if (item->type()==ElemType::UNPASSABLE) 
			return false;
	}

	return true;
}

QRectF PlayerGraphicsItem::boundingRect() const {
	return QRectF(-R, -R, 2*R, 2 * R);
}

QPainterPath PlayerGraphicsItem::shape() const {
	QPainterPath path;
	// 注意有一圈描边
	path.addEllipse(-R, -R, 2 * R, 2 * R);
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
