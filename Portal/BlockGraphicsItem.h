#pragma once
	
#include "Map.h"

#include "GraphicsItem.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>

class Map;

class BlockGraphicsItem : public GraphicsItem {
public:
	//GraphicsBlockItem(const QRect& rect = QRect(0, 0, 32, 32), 
	//	const QPixmap& img = QPixmap(), QGraphicsItem* parent = nullptr);
	BlockGraphicsItem(int BlockSize = 1);
	
	// 使用默认构造
	BlockGraphicsItem(const QPoint& index, Map* map = NULL);
	BlockGraphicsItem(int x, int y, Map* map = NULL);
	BlockGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), Map* map = NULL);
	BlockGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), Map* map = NULL);
	
	QRectF boundingRect() const override;

	void setMap(Map* map);

	void setImg(const QPixmap& img);

	bool isAccessible() const override;

protected:
	Map* parentMap;

	QPixmap img;

	virtual void initial(const QPoint& index, const QPixmap& img, Map* map);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};