#pragma once

#include "BlockGraphicsItem.h"
#include "MapGame.h"

class BlockGameGraphicsItem : public BlockGraphicsItem {

public:
	BlockGameGraphicsItem(MapGame* map);

	// 使用默认构造
	BlockGameGraphicsItem(const QPoint& index, Map* map = NULL);
	BlockGameGraphicsItem(int x, int y, Map* map = NULL);
	BlockGameGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), Map* map = NULL);
	BlockGameGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), Map* map = NULL);

private:
	void paintDoor(QPainter* painter, BlockGraphicsItem::Side side);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};