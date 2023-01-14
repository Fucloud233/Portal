#pragma once

#include "MapGraphicsView.h"
#include "BlockEditGraphicsItem.h"
#include "MapEdit.h"

class MapEditorGraphicsView : public MapGraphicsView {
	Q_OBJECT
public:
	MapEditorGraphicsView(QWidget* parent = nullptr);

	// 初始化地图 用于编辑地图
	void intialMap();

private:
	BlockEditGraphicsItem* highlightArea;
	QPoint m_last_pos;

	void addItems();

	void testPaint();

	void mousePressEvent(QMouseEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);

private slots:
	void updateBlock();

signals:
	void selectBlock(BlockStatus* status);
};
