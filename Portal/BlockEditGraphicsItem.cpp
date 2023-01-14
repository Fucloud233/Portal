#include "BlockEditGraphicsItem.h"

#include <QCursor>
#include <QPen>

BlockEditGraphicsItem::BlockEditGraphicsItem(MapEdit* map):
	BlockGraphicsItem(map) {
}

BlockEditGraphicsItem::BlockEditGraphicsItem(const QPoint& index, const QPixmap& img, Map* map) :
	BlockGraphicsItem(map) {
	initial(index, img, map);
}

BlockEditGraphicsItem::BlockEditGraphicsItem(int x, int y, const QPixmap& img, Map* map) :
	BlockEditGraphicsItem(QPoint(x, y), img, map) {
}

BlockEditGraphicsItem::BlockEditGraphicsItem(const QPoint& index, Map* map) :
	BlockEditGraphicsItem(index, QPixmap(), map) {
}

BlockEditGraphicsItem::BlockEditGraphicsItem(int x, int y, Map* map) :
	BlockEditGraphicsItem(QPoint(x, y), QPixmap(), map) {
}

void BlockEditGraphicsItem::setHeight(Height height) {
	// 当没有被选择时 需要记录原始高度
	if (height != SELECTED) {
		origin_height = height;
	}

	setZValue(height);
}

void BlockEditGraphicsItem::initial(const QPoint& index, const QPixmap& img, Map* map) {

	BlockGraphicsItem::initial(index, img, map);
	
	// 当图片为空时 加载此函数
	if (img.isNull()) {
		QPixmap emptyImg(blockSize, blockSize);
		emptyImg.fill(Qt::transparent);

		QPainter painter(&emptyImg);
		painter.setPen(QPen(Qt::gray, 1.5));
		//painter.setBrush(Qt::white);
		painter.drawRect(0, 0, blockSize, blockSize);
		
		setPixmap(emptyImg);
		setHeight(DRAFT);
	}
}

// 按下鼠标
void BlockEditGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();

	// 当位置合法 且不为空时 才进行移动
	if (parentMap->translatePos(point) && !parentMap->isNULL(point)) {
		setFocus();
		m_origin_pos = point;
		QGraphicsItem::mousePressEvent(event);
	}

	// 设置当前选择的位置
	((MapEdit*)parentMap)->setSelectedPos(point);
}

// 鼠标移动
void BlockEditGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QPoint point = event->scenePos().toPoint();
	parentMap->translatePos(point);

	if (point != m_origin_pos) {
		setPos(point);
		((MapEdit* )parentMap)->swap(m_origin_pos, getPos());
		m_origin_pos = getPos();
	}

	// 设置当前选择的位置
	((MapEdit*)parentMap)->setSelectedPos(point);
}

void BlockEditGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	clearFocus();
}

void BlockEditGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
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