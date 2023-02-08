#include "BulletGraphicsItem.h"


BulletGraphicsItem::BulletGraphicsItem(Qt::GlobalColor color, qreal angle, const QPointF& pos) {
	// 设置基本属性
	setPos(pos);
	this->angle = angle;
	this->color = color;
	speed = 5;
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
	int flag = true;

	QList<QGraphicsItem*> items = collidingItems(Qt::IntersectsItemShape);
	for (int i = 0; i < items.size(); i++) {
		BlockGraphicsItem* item = qgraphicsitem_cast<BlockGraphicsItem*>(items[i]);
		if (item->type() == GraphicsItem::UNPASSABLE || item->type() == BlockGameGraphicsItem::RED_DOOR || item->type() == BlockGameGraphicsItem::BLUE_DOOR) {

			Block::Side side = item->SideAbout(this);

			//// 计算所在侧面
			//Block::Side side;
			//// 记录两点的差值
			//QPointF diff = this->scenePos() - item->scenePos();
			//// 计算这个差值与BlockSize的差值
			//QPointF sizeDiff(qAbs(diff.x())-24, qAbs(diff.y())-24);

			//if (sizeDiff.x() > 0) {
			//	if (diff.x() > 0)
			//		side = Block::RIGHT;
			//	else
			//		side = Block::LEFT;
			//}
			//else {
			//	if (diff.y() > 0)
			//		side = Block::DOWN;
			//	else
			//		side = Block::UP;
			//}

			emit collideWall(item->Index(), side, color==Qt::red);

			flag = false;
		}
	}

	return flag	;
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
