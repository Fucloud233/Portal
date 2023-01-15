#pragma once

#include "BlockGraphicsItem.h"
#include "MapEdit.h"

class MapEdit;

class BlockEditGraphicsItem : public BlockGraphicsItem {
public:
	BlockEditGraphicsItem(int BlockSize = 1);
	BlockEditGraphicsItem(MapEdit* map);

	BlockEditGraphicsItem(const QPoint& index, MapEdit* map = NULL);
	BlockEditGraphicsItem(int x, int y, MapEdit* map = NULL);
	BlockEditGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), MapEdit* map = NULL);
	BlockEditGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), MapEdit* map = NULL);

	void setHeight(Height height);

private:
	QPoint m_origin_pos;
	Height origin_height;

	void initial(const QPoint& index, const QPixmap& img, MapEdit* map);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};