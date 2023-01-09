#pragma once

#include "Map.h"

#include <QGraphicsItem>
#include <QRect>
#include <QPixmap>
#include <QGraphicsSceneEvent>

class GraphicsBlockItem: 
	public QGraphicsPixmapItem
{
public:
	//GraphicsBlockItem(const QRect& rect = QRect(0, 0, 32, 32), 
	//	const QPixmap& img = QPixmap(), QGraphicsItem* parent = nullptr);
	GraphicsBlockItem();
	GraphicsBlockItem(const QPoint& index, const QPixmap& img, const Map* map = NULL);

	inline void setPos(const QPoint& point);
	inline void setPos(int x, int y);


private:
	int blockSize;
	const Map* map;
	QPoint m_origin_point;
	
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

};
Q_DECLARE_METATYPE(GraphicsBlockItem)