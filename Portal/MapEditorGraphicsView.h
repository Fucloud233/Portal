#pragma once

#include "MapGraphicsView.h"

class MapEditorGraphicsView : public MapGraphicsView {
	Q_OBJECT
public:
	MapEditorGraphicsView(QWidget* parent = nullptr);

	// 初始化地图
	void intialMap();
	bool saveMap(QString filePath);
	bool loadMap(QString filePath);

private:
	BlockEditGraphicsItem* highlightArea;
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
