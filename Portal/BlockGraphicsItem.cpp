#include "BlockGraphicsItem.h"

BlockGraphicsItem::BlockGraphicsItem(Map* map) :
	QGraphicsPixmapItem(nullptr) {
	
	parentMap = map;
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

void BlockGraphicsItem::setHeight(Height height) {
	setZValue(height);
}

void BlockGraphicsItem::setImg(const QPixmap& img) {
	QGraphicsPixmapItem::setPixmap(img);
	if (img.width()&&blockSize) 
		setScale(blockSize / img.width());
}

QPoint BlockGraphicsItem::getPos() const  {
	return index;
}


void BlockGraphicsItem::initial(const QPoint& index, const QPixmap& img, Map* map) {
	setAcceptedMouseButtons(Qt::LeftButton);

	// 设置基本属性
	setMap(map);
	setImg(img);
	setHeight(BOTTOM);
	setPos(index);

	// 设置状态
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

void BlockGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	// 画图原始的图形
	painter->drawPixmap(0, 0, pixmap());

	// 当类型为FLOOR时 为图案添加一层阴影
	if (parentMap->getBlockStatus(index)->getBlockType() == Block::FLOOR) {
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0, 0, 0, 127));
		painter->drawRect(QRect(QPoint(0, 0), pixmap().size()));
	}
}
