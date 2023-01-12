#pragma once
	
#include "Map.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>

class Map;

class BlockGraphicsItem: 
	public QGraphicsPixmapItem
{
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

	inline void setMap(Map* map);
	inline void setPos(const QPoint& point);
	inline void setPos(int x, int y);
	inline void setX(int x);
	inline void setY(int y);
	inline void setImg(const QPixmap& img);
	inline void setHeight(Height height);

	inline QPoint getPos() const;

private:
	int blockSize;
	Map* parentMap;
	QPoint m_origin_pos;
	Height origin_height;
	
	// 存储相对坐标
	QPoint index;

	void initial(const QPoint& index, const QPixmap& img, Map* map);

	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};