#pragma once
	
#include "Map.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>

class Map;

class BlockGraphicsItem : public QGraphicsPixmapItem {
public:
	enum Height {
		DRAFT = 0, BOTTOM = 1, ON = 2, SELECTED = 3, TOP = 4
	};

	//GraphicsBlockItem(const QRect& rect = QRect(0, 0, 32, 32), 
	//	const QPixmap& img = QPixmap(), QGraphicsItem* parent = nullptr);
	BlockGraphicsItem(Map* map = NULL);
	
	// 使用默认构造
	BlockGraphicsItem(const QPoint& index, Map* map = NULL);
	BlockGraphicsItem(int x, int y, Map* map = NULL);
	BlockGraphicsItem(const QPoint& index, const QPixmap& img = QPixmap(), Map* map = NULL);
	BlockGraphicsItem(int x, int y, const QPixmap& img = QPixmap(), Map* map = NULL);
	
	QRectF boundingRect() const override;

	void setMap(Map* map);
	void setPos(const QPoint& point);
	void setPos(int x, int y);
	void setX(int x);
	void setY(int y);
	void setImg(const QPixmap& img);
	virtual void setHeight(Height height);

	QPoint getPos() const;

protected:
	int blockSize;

	Map* parentMap;
	
	// 存储相对坐标
	QPoint index;

	virtual void initial(const QPoint& index, const QPixmap& img, Map* map);
};