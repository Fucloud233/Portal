#pragma once

#include "Map.h"
#include "BlockInfoOperator.h"
#include "BlockGraphicsItem.h"

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
	BlockGraphicsItem* highlightArea;
	
	QPoint m_last_pos;
	
	void intial();
	void testPaint();

	void mousePressEvent(QMouseEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);

private slots:
	void updateBlock();

signals:
	void selectBlock();
};