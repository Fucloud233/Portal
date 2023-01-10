#include "GraphicsBlockItem.h"

#include <QRect>
#include <QPixmap>
#include <QCursor>

GraphicsBlockItem::GraphicsBlockItem(Map* map) :
	QGraphicsPixmapItem(nullptr) {
	
	setMap(map);
}

GraphicsBlockItem::GraphicsBlockItem(int x, int y, const QPixmap& img, Map* map) :
	QGraphicsPixmapItem(nullptr) {
	

	initial(QPoint(x, y), img, map);
}

GraphicsBlockItem::GraphicsBlockItem(const QPoint& index, const QPixmap& img, Map* map) :
	QGraphicsPixmapItem(nullptr) {

	initial(index, img, map);
}

QRectF GraphicsBlockItem::boundingRect() const {
	return QRectF(0, 0, blockSize, blockSize);
}

void GraphicsBlockItem::initial(const QPoint& index, const QPixmap& img, Map* map) {

	// 设置基本属性
	setMap(map);
	setImg(img);
	this->setPos(index);

	// 设置状态
	this->setFlag(QGraphicsItem::ItemIsFocusable);
	this->setFlag(QGraphicsItem::ItemIsSelectable);

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
	if (parentMap->checkX(x)) setX(x);
	if (parentMap->checkY(y)) setY(y);

	QGraphicsPixmapItem::setPos(this->x(), this->y());
}

void GraphicsBlockItem::setPos(const QPoint& point) {
	setPos(point.x(), point.y());
}

void GraphicsBlockItem::setX(int x) {
	QGraphicsPixmapItem::setX(x * blockSize);
	index.setX(x);
}

void GraphicsBlockItem::setY(int y) {
	QGraphicsPixmapItem::setY(y * blockSize);
	index.setY(y);
}

void GraphicsBlockItem::setImg(const QPixmap& img) {
	QGraphicsPixmapItem::setPixmap(img);
	if (img.width()&&blockSize) 
		setScale(blockSize / img.width());
}


QPoint GraphicsBlockItem::getPos() const  {
	return index;
}

// 按下鼠标
void GraphicsBlockItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	setFocus();

	QPoint point = event->scenePos().toPoint();	
	if (!parentMap->translatePos(point)) {
		return;
	}
	
	m_origin_pos = point;

	QGraphicsItem::mousePressEvent(event);
}

// 鼠标移动
void GraphicsBlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	parentMap->translatePos(point);

	if (point != m_origin_pos) {
		setPos(point);
		parentMap->swap(m_origin_pos, getPos());
		m_origin_pos = getPos();
	}
}

void GraphicsBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	clearFocus();

}

void GraphicsBlockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setPen(Qt::NoPen);
	
	//painter->drawPixmap(0, 0, blockSize, blockSize, pixmap());
	painter->drawPixmap(0, 0, pixmap());

	this->setZValue(1);

	if (isSelected()) {
		this->setCursor(Qt::OpenHandCursor);
		//qDebug() << parentMap->getBlock(index).BlockName();
		painter->setPen(QPen(Qt::blue, 1.5));
		painter->drawRect(QRect(QPoint(0, 0), pixmap().size()));
		
		this->setZValue(5);
	}
}