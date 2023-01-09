#pragma once

#include "Map.h"

#include "BlockInfoOperator.h"

#include <QGraphicsView>
#include <QtWidgets>

class MapGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	explicit MapGraphicsView(Map* map, BlockInfoOperator* Operator, QWidget* parent = nullptr);

private:
	static int BlockSize;

	BlockInfoOperator* Operator;

	Map* map;
	QGraphicsScene* scene;

	QGraphicsPixmapItem* highlightArea;
	
	
	void intial();
	void testPaint();

	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);
};