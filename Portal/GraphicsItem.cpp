#include "GraphicsItem.h"

GraphicsItem::GraphicsItem(int blockSize) :
	QGraphicsItem(nullptr) {
	this->blockSize = blockSize;
	index = QPoint(0, 0);
}

void GraphicsItem::setPos(int x, int y) {
	GraphicsItem::setPos(QPoint(x, y));
}

void GraphicsItem::setPos(const QPoint& point) {
	QGraphicsItem::setPos(point.x() * blockSize, point.y() * blockSize);
	index = point;
}

void GraphicsItem::setX(int x) {
	QGraphicsItem::setX(x * blockSize);
	index.setX(x);
}

void GraphicsItem::setY(int y) {
	QGraphicsItem::setY(y * blockSize);
	index.setY(y);
}

void GraphicsItem::setHeight(Height height) {
	setZValue(height);
}

QPoint GraphicsItem::getPos() const {
	return index;
}