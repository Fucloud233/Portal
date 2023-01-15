#include "BlockGraphicsItem.h"

BlockGraphicsItem::BlockGraphicsItem(int BlockSize) :
	GraphicsItem(BlockSize) {
}

BlockGraphicsItem::BlockGraphicsItem(const QPoint& index, const QPixmap& img, Map* map) :
	GraphicsItem(map ? map->BlockSize() : 1) {

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
	return QRectF(0, 0, blockSize/scale(), blockSize / scale());
}

void BlockGraphicsItem::setMap(Map* map) {
	parentMap = map;
	blockSize = map ? map->BlockSize() : 0;
}

void BlockGraphicsItem::setImg(const QPixmap& img) {
	this->img = img;
	if (img.width() && blockSize)
		setScale(blockSize / img.width());
}

bool BlockGraphicsItem::isAccessible() const {
	return parentMap->getBlockStatus(index)->getBlockType() == Block::FLOOR;
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
	painter->drawPixmap(0, 0, img);

	// 检测边界
	//painter->setPen(QPen(Qt::red, 1.5));
	//painter->drawRect(boundingRect());

	// 当类型为FLOOR时 为图案添加一层阴影
	if (parentMap->getBlockStatus(index)->getBlockType() == Block::FLOOR) {
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0, 0, 0, 127));
		painter->drawRect(QRect(QPoint(0, 0), img.size()));
	}
}
