#pragma once
	
#include "Map.h"

#include "GraphicsItem.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QtMath>

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
	
	void setPos(const QPoint& point);
	void setPos(int x, int y);
	void setX(int x);
	void setY(int y);

	QPoint getPos() const;
	int x() const;
	int y() const;

	QRectF boundingRect() const override;
	int type() const override;

	void setMap(Map* map);
	void setImg(const QPixmap& img);

protected:
	// 记录相对坐标
	QPoint index;
	QPixmap img;

	Map* parentMap;

	virtual void initial(const QPoint& index, const QPixmap& img, Map* map);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};