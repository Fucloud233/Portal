#include "BlockGraphicsItem.h"

#include <QPen>
#include <QRect>
#include <QPixmap>
#include <QCursor>

BlockGraphicsItem::BlockGraphicsItem(Map* map) :
	QGraphicsPixmapItem(nullptr) {
	
	initial(QPoint(), QPixmap(), map);
}

BlockGraphicsItem::BlockGraphicsItem(const QPoint& index, const QPixmap& img, Map* map) :
	QGraphicsPixmapItem(nullptr) {

	initial(index, img, map);
}

BlockGraphicsItem::BlockGraphicsItem(int x, int y, const QPixmap& img, Map* map) :
	BlockGraphicsItem(QPoint(x, y), img,  map){
}

BlockGraphicsItem::BlockGraphicsItem(const QPoint& index, Map* map) :
	BlockGraphicsItem(index, QPixmap(), map) {
}

BlockGraphicsItem::BlockGraphicsItem(int x, int y, Map* map) :
	BlockGraphicsItem(QPoint(x, y), QPixmap(), map) {
}

QRectF BlockGraphicsItem::boundingRect() const {
	return QRectF(0, 0, blockSize, blockSize);
}

void BlockGraphicsItem::initial(const QPoint& index, const QPixmap& img, Map* map) {

	this->setAcceptedMouseButtons(Qt::LeftButton);

	// 设置基本属性
	setMap(map);
	setImg(img);
	this->setPos(index);

	// 设置状态
	this->setFlag(QGraphicsItem::ItemIsFocusable);
	this->setFlag(QGraphicsItem::ItemIsSelectable);
}

void BlockGraphicsItem::setMap(Map* map) {
	parentMap = map;
	blockSize = map ? map->BlockSize() : 0;
}

void BlockGraphicsItem::setPos(int x, int y) {
	if (parentMap->checkX(x)) setX(x);
	if (parentMap->checkY(y)) setY(y);

	QGraphicsPixmapItem::setPos(this->x(), this->y());
}

void BlockGraphicsItem::setPos(const QPoint& point) {
	setPos(point.x(), point.y());
}

void BlockGraphicsItem::setX(int x) {
	QGraphicsPixmapItem::setX(x * blockSize);
	index.setX(x);
}

void BlockGraphicsItem::setY(int y) {
	QGraphicsPixmapItem::setY(y * blockSize);
	index.setY(y);
}

void BlockGraphicsItem::setImg(const QPixmap& img) {
	QGraphicsPixmapItem::setPixmap(img);
	if (img.width()&&blockSize) 
		setScale(blockSize / img.width());
}

QPoint BlockGraphicsItem::getPos() const  {
	return index;
}

// 按下鼠标
void BlockGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();	
	if (parentMap->translatePos(point)) {
		setFocus();
		parentMap->setSelectedPos(point);
		m_origin_pos = point;
		QGraphicsItem::mousePressEvent(event);
	}
}

// 鼠标移动
void BlockGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	parentMap->translatePos(point);

	if (point != m_origin_pos) {
		setPos(point);
		parentMap->swap(m_origin_pos, getPos());
		m_origin_pos = getPos();
	}
}

void BlockGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	clearFocus();
}

void BlockGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

	this->setZValue(1);

	// 设置默认构造
	if (pixmap().isNull()) {
		painter->setPen(QPen(Qt::gray, 1.5));
		//painter->setBrush(Qt::white);
		painter->drawRect(0, 0, blockSize, blockSize);
		return;
	}

	painter->drawPixmap(0, 0, pixmap());

	if (isSelected()) {
		this->setCursor(Qt::OpenHandCursor);
		//qDebug() << parentMap->getBlock(index).BlockName();
		painter->setPen(QPen(Qt::blue, 1.5));
		painter->drawRect(QRect(QPoint(0, 0), pixmap().size()));
		
		this->setZValue(5);
	}
}