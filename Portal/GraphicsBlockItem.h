#pragma once
	
#include "Map.h"

#include <QGraphicsItem>
#include <QRect>
#include <QPixmap>
#include <QGraphicsSceneEvent>

class Map;

class GraphicsBlockItem: 
	public QGraphicsPixmapItem
{
public:
	//GraphicsBlockItem(const QRect& rect = QRect(0, 0, 32, 32), 
	//	const QPixmap& img = QPixmap(), QGraphicsItem* parent = nullptr);
	GraphicsBlockItem(Map* map = NULL);
	GraphicsBlockItem(const QPoint& index, const QPixmap& img, Map* map);
	GraphicsBlockItem(int x, int y, const QPixmap& img, Map* map);

	inline void setMap(Map* map);
	inline void setPos(const QPoint& point);
	inline void setPos(int x, int y);
	inline void setImg(const QPixmap& img);

private:
	int blockSize;
	Map* parentMap;
	QPoint m_origin_pos;
	QPoint m_last_pos;

	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};
Q_DECLARE_METATYPE(GraphicsBlockItem)