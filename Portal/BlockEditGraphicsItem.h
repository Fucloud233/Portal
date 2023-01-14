#pragma once

#include "BlockGraphicsItem.h"
#include "MapEdit.h"

class MapEdit;

class BlockEditGraphicsItem : public BlockGraphicsItem {
public:
	BlockEditGraphicsItem(MapEdit* map = NULL);

	BlockEditGraphicsItem(const QPoint& index, Map* map = NULL);
	BlockEditGraphicsItem(int x, int y, Map* map = NULL);
	BlockEditGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), Map* map = NULL);
	BlockEditGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), Map* map = NULL);

	void setHeight(Height height);
private:
	QPoint m_origin_pos;
	Height origin_height;


	void initial(const QPoint& index, const QPixmap& img, Map* map);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};