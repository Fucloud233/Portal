#include "BulletGraphicsItem.h"

BulletGraphicsItem::BulletGraphicsItem(Qt::GlobalColor color, qreal angle, int speed, const QPointF& pos) {
	setPos(pos);
	this->angle = angle;
	this->speed = speed;
	this->color = color;
	R = 8;

	// 多线程处理
	thread = new BulletThread;
	connect(thread, &BulletThread::flying, this, &BulletGraphicsItem::fly); 
	connect(thread, &BulletThread::finished, this, &QObject::deleteLater);
	thread->start();
}

void BulletGraphicsItem::fly() {
	QPointF originPos = pos();
	// 控制飞行
	if (checkcolliding()) {
		setX(x() + qCos(angle) * speed);
		setY(y() + qSin(angle) * speed);
	}
	else {
		setPos(originPos);
		thread->end();
		
	}
}

bool BulletGraphicsItem::checkcolliding() {

	QList<QGraphicsItem*> items = collidingItems(Qt::IntersectsItemShape);
	for (int i = 0; i < items.size(); i++) {
		BlockGraphicsItem* item = qgraphicsitem_cast<BlockGraphicsItem*>(items[i]);
		if (item->type() == GraphicsItem::UNPASSABLE) {

			// 处理碰撞
			// 1.计算位置

			return false;
		}
	}

	return true;
}

QPainterPath BulletGraphicsItem::shape() const {
	QPainterPath path;
	path.addEllipse(QPointF(0, 0), R, R);

	return path;
}

QRectF BulletGraphicsItem::boundingRect() const {
	return QRectF(-R, -R, 2 * R, 2 * R);
}

void BulletGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setPen(QPen(Qt::black, 1));
	painter->setBrush(color);
	painter->drawEllipse(QPoint(0, 0),R ,R);
	//painter->drawRect(boundingRect());
}
