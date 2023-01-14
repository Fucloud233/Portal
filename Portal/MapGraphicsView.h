#pragma once

#include "BlockInfoOperator.h"
#include "BlockGraphicsItem.h"

#include <QGraphicsView>
#include <QtWidgets>

#define Operator BlockInfoOperator 

class MapGraphicsView :public QGraphicsView {
	Q_OBJECT
public:
	MapGraphicsView(QWidget* parent = nullptr);

	virtual bool saveMap(QString filePath);
	virtual bool loadMap(QString filePath);
protected:
	static int BlockSize;

	Map* map;
	QGraphicsScene* scene;

	// 根据Map提供的接口来初始化Scene
	virtual void addItems();
};