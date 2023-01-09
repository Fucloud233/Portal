#pragma once

#include "Map.h"

#include <QGraphicsView>
#include <QtWidgets>

class MapGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	explicit MapGraphicsView(Map* map, QWidget* parent = nullptr);

private:
	static int BlockSize;

	Map* map;
	QGraphicsScene* scene;

	QGraphicsRectItem* highlight_rect;
	
	
	void paint();
	void testPaint();

	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);
};