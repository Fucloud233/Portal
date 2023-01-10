#include "GraphicsBlockItem.h"

#include <QRect>
#include <QPixmap>

GraphicsBlockItem::GraphicsBlockItem(Map* map) :
	QGraphicsPixmapItem(nullptr) {
	
	setMap(map);
}

GraphicsBlockItem::GraphicsBlockItem(int x, int y, const QPixmap& img, Map* map) :
	QGraphicsPixmapItem(nullptr) {
	
	setMap(map);
	setImg(img);
	this->setPos(x, y);
}

GraphicsBlockItem::GraphicsBlockItem(const QPoint& index, const QPixmap& img, Map* map) :
	QGraphicsPixmapItem(nullptr) {

	setMap(map);
	setImg(img);
	this->setPos(index);
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


void GraphicsBlockItem::setMap(Map* map) {
	parentMap = map;
	blockSize = map ? map->BlockSize() : 0;
}

void GraphicsBlockItem::setPos(int x, int y) {
	QGraphicsPixmapItem::setPos(x * blockSize, y * blockSize);
}

void GraphicsBlockItem::setPos(const QPoint& point) {
	QGraphicsPixmapItem::setPos(point.x() * blockSize, point.y() * blockSize);
}

inline void GraphicsBlockItem::setImg(const QPixmap& img) {
	QGraphicsPixmapItem::setPixmap(img);
	if (img.width()&&blockSize) 
		setScale(blockSize / img.width());
}

void GraphicsBlockItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();	
	if (!parentMap->translatePos(point)) {
		return;
	}
	
	m_origin_pos = point;

	QGraphicsItem::mousePressEvent(event);
}

void GraphicsBlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	parentMap->translatePos(point);
	
	if (parentMap->checkX(point.x()))
		m_last_pos.setX(point.x());
	if (parentMap->checkY(point.y()))
		m_last_pos.setY(point.y());

	if (m_origin_pos != m_last_pos) {
		parentMap->swap(m_origin_pos, m_last_pos);
		m_origin_pos = m_last_pos;
	}
}

//void GraphicsBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
//}