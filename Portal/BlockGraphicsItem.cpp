#include "BlockGraphicsItem.h"

#include <QPen>
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

	if (img.isNull()) {
		QPixmap emptyImg(blockSize, blockSize);
		emptyImg.fill(Qt::transparent);

		QPainter painter(&emptyImg);
		painter.setPen(QPen(Qt::gray, 1.5));
		//painter.setBrush(Qt::white);
		painter.drawRect(0, 0, blockSize, blockSize);
		
		setImg(emptyImg);
		this->setHeight(DRAFT);
	}
	else {
		setImg(img);
		this->setHeight(BOTTOM);
	}

	setPos(index);

	// 设置状态
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsSelectable);
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
	// 当没有被选择时 需要记录原始高度
	if (height != SELECTED) {
		origin_height = height;
	}

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

// 按下鼠标
void BlockGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();	

	// 当位置合法 且不为空时 才进行移动
	if (parentMap->translatePos(point)&&!parentMap->isNULL(point)) {
		setFocus();
		m_origin_pos = point;
		QGraphicsItem::mousePressEvent(event);
	}

	// 设置当前选择的位置
	parentMap->setSelectedPos(point);
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
	// 画图原始的图形
	painter->drawPixmap(0, 0, pixmap());
	
	// 当类型为FLOOR时 为图案添加一层阴影
	if (parentMap->getBlockStatus(index)->getBlockType() == Block::FLOOR) {
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0, 0, 0, 127));
		painter->drawRect(QRect(QPoint(0, 0), pixmap().size()));
	}

	// 当Block被选择时 为其绘制方框
	if (isSelected()) {
		this->setCursor(Qt::OpenHandCursor);
		//qDebug() << parentMap->getBlock(index).BlockName();
		painter->setPen(QPen(Qt::blue, 1));
		painter->setBrush(Qt::NoBrush);
		painter->drawRect(QRect(QPoint(0, 0), pixmap().size()));

		// 注意 选择的时候 要拔高高度
		setHeight(SELECTED);
	}
	else {
		setHeight(origin_height);
	}
}