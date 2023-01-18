#pragma once

#include "GraphicsItem.h"

#include "Map.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QtMath>

class Map;

class BlockGraphicsItem : public GraphicsItem {
public:
	enum Side {
		UP, DOWN, LEFT, RIGHT
	};

	//GraphicsBlockItem(const QRect& rect = QRect(0, 0, 32, 32), 
	//	const QPixmap& img = QPixmap(), QGraphicsItem* parent = nullptr);
	BlockGraphicsItem(Map* map = NULL);
	
	// 使用默认构造
	BlockGraphicsItem(const QPoint& index, Map* map = NULL);
	BlockGraphicsItem(int x, int y, Map* map = NULL);
	BlockGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), Map* map = NULL);
	BlockGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), Map* map = NULL);
	
	void setPos(const QPoint& point);
	void setPos(int x, int y);
	void setX(int x);
	void setY(int y);

	QPoint getPos() const;
	int x() const;
	int y() const;

	QPainterPath shape() const override;
	QRectF boundingRect() const override;
	int type() const override;

	void setImg(const QPixmap& img);
	void setHeight(Height height) override;

protected:
	Map* parentMap;

	// 记录相对坐标
	QPoint index;
	QPixmap img;
	Height origin_height;

	virtual void initial(const QPoint& index, const QPixmap& img, Map* map);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};