#pragma once

#include "Map.h"
#include "BlockInfoOperator.h"
#include "BlockGraphicsItem.h"

#include <QGraphicsView>
#include <QtWidgets>

#define Operator BlockInfoOperator 

class MapGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	explicit MapGraphicsView(QWidget* parent = nullptr);

	// 初始化地图
	void intialMap();
	bool saveMap(QString filePath);
	bool loadMap(QString filePath);

private:
	static int BlockSize;

	Map* map;
	QGraphicsScene* scene;
	BlockGraphicsItem* highlightArea;
	
	QPoint m_last_pos;
	
	void initialScene();

	void testPaint();

	void mousePressEvent(QMouseEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);

private slots:
	void updateBlock();

signals:
	void selectBlock(BlockStatus* status);
};