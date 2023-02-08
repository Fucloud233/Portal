#include "BlockGraphicsItem.h"

BlockGraphicsItem::BlockGraphicsItem(Map* map) {
}

BlockGraphicsItem::BlockGraphicsItem(const QPoint& index, const QPixmap& img, Map* map) {
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

Block::Side BlockGraphicsItem::SideAbout(QGraphicsItem* item) {
	QPoint point = item->scenePos().toPoint() / blockSize ;
	QPoint diff = point - index;

	int distance = (qAbs(diff.x()) + qAbs(diff.y()));

	if (distance == 1) {
		if (diff.x() > 0)
			return Block::RIGHT;
		else if (diff.x() < 0)
			return Block::LEFT;
		else if (diff.y() > 0)
			return Block::DOWN;
		else if (diff.y() < 0)
			return Block::UP;
	}
	else if (distance == 0) {
		return Block::CENTER;
	}
	else
		return Block::INVALID;
}

QPoint BlockGraphicsItem::SidePos(Block::Side side) {
	switch (side) {
	case Block::UP:
		return index + QPoint(0, -1);
	case Block::DOWN:
		return index + QPoint(0, 1);
	case Block::LEFT:
		return index + QPoint(-1, 0);
	case Block::RIGHT:
		return index + QPoint(1, 0);
	default:
		return index;
	}
}

void BlockGraphicsItem::initial(const QPoint& index, const QPixmap& img, Map* map) {
	// 设置基本属性
	parentMap = map;
	setImg(img);
	setHeight(BOTTOM);
	setPos(index);

	// 设置状态
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

int BlockGraphicsItem::type() const {
	if (parentMap->Status(index)->getBlockType() == Block::FLOOR) 
		return ElemType::PASSABLE;
	else 
		return ElemType::UNPASSABLE;
}

void BlockGraphicsItem::setImg(const QPixmap& img) {
	this->img = img;
	//if (img.width() && blockSize)
	//	setScale(blockSize / img.width());
}

void BlockGraphicsItem::setPos(int x, int y) {
	GraphicsItem::setPos(QPoint(x, y));
}

void BlockGraphicsItem::setPos(const QPoint& point) {
	QGraphicsItem::setPos(point.x() * blockSize, point.y() * blockSize);
	index = point;
}

void BlockGraphicsItem::setX(int x) {
	QGraphicsItem::setX(x * blockSize);
	index.setX(x);
}

void BlockGraphicsItem::setY(int y) {
	QGraphicsItem::setY(y * blockSize);
	index.setY(y);
}

QPoint BlockGraphicsItem::Index() const {
	return index;
}

int BlockGraphicsItem::x() const {
	return index.x();
}
int BlockGraphicsItem::y() const {
	return index.y();
}

void BlockGraphicsItem::setHeight(Height height) {
	// 当没有被选择时 需要记录原始高度
	if (height != SELECTED) {
		origin_height = height;
	}

	setZValue(height);
}

QPainterPath BlockGraphicsItem::shape() const {
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

QRectF BlockGraphicsItem::boundingRect() const {
	//int size = blockSize / scale();
	return QRectF(-blockSize / 2, -blockSize / 2, blockSize, blockSize);
}

void BlockGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	// 画图原始的图形
	painter->drawPixmap(boundingRect().toRect(), img);

	// 检测边界
	//painter->setPen(QPen(Qt::red, 1.5));
	//painter->drawRect(boundingRect());

	// 当类型为FLOOR时 为图案添加一层阴影
	if (parentMap->Status(index)->getBlockType() == Block::FLOOR) {
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0, 0, 0, 127));
		painter->drawRect(boundingRect());
	}
}
