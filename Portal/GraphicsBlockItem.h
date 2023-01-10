#pragma once
	
#include "Map.h"

#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
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

	QRectF boundingRect() const override;

	inline void setMap(Map* map);
	inline void setPos(const QPoint& point);
	inline void setPos(int x, int y);
	inline void setX(int x);
	inline void setY(int y);
	inline void setImg(const QPixmap& img);

	inline QPoint getPos() const;

private:
	int blockSize;
	Map* parentMap;
	QPoint m_origin_pos;
	
	// 存储相对坐标
	QPoint index;

	void initial(const QPoint& index, const QPixmap& img, Map* map);

	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};
Q_DECLARE_METATYPE(GraphicsBlockItem)