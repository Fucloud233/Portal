#include "GraphicsBlockItem.h"

#include <QRect>
#include <QPixmap>

GraphicsBlockItem::GraphicsBlockItem() {
	this->blockSize = 32;
	this->map = NULL;
}

GraphicsBlockItem::GraphicsBlockItem(const QPoint& index, const QPixmap& img, const Map* map) :
	QGraphicsPixmapItem(img, nullptr) {
	this->blockSize = map->BlockSize();

	this->setPos(index);

	if (!img.isNull())
		this->setScale(blockSize / img.width());

	this->map = map;
}

//GraphicsBlockItem::GraphicsBlockItem(const QRect& rect, const QPixmap& img, QGraphicsItem* parent) :
//	QGraphicsPixmapItem(img, parent){
//
//	this->setPos(rect.x(), rect.y());
//
//	if (!img.isNull())
//		this->setScale(rect.width() / img.width());
//	else
//		this->setScale(1);
//}

void GraphicsBlockItem::setPos(int x, int y) {
	this->QGraphicsPixmapItem::setPos(x * blockSize, y * blockSize);
}

void GraphicsBlockItem::setPos(const QPoint& point) {
	this->QGraphicsPixmapItem::setPos(point.x() * blockSize, point.y() * blockSize);
}

void GraphicsBlockItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	if (!map->translatePos(point)) {
		return;
	}
	
	m_origin_point = point;

	QGraphicsItem::mousePressEvent(event);
}


void GraphicsBlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	if (!map->translatePos(point)) {
		return;
	}
	this->setPos(point);
	this->update();
}