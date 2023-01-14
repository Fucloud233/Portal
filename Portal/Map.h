#pragma once

#include "Matrix.h"
#include "Block.h"
#include "BlockStatus.h"
#include "BlockGraphicsItem.h"
#include "BlockInfoOperator.h"

#include <QGraphicsItem>

class BlockGraphicsItem;

class Map {
protected:
	//Matrix<Block*> data;
	Matrix<BlockStatus*> statuses;
	Matrix<BlockGraphicsItem*> items;

	int blockSize;
	int width, height;
public:
	Map(int blockSize = 48);
	~Map();

	virtual void initial(int width = 10, int height = 10);

	bool modify(int x, int y, int blockCode, BlockStatus* status = NULL);
	bool modify(const QPoint& point, int blockCode, BlockStatus* status = NULL);

	bool translatePos(QPoint& point) const;
	
	bool checkPos(int x, int y) const;
	bool checkPos(const QPoint& point) const;
	bool checkX(int x) const;
	bool checkY(int y) const;
	bool isNULL(const QPoint& point) const;

	int BlockSize() const;

	BlockStatus* getBlockStatus(const QPoint& point) const;
	BlockStatus* getBlockStatus(int x, int y) const;
	BlockGraphicsItem* getItem(const QPoint& point) const;
	BlockGraphicsItem* getItem(int x, int y) const;
	QList<BlockGraphicsItem*> getItems();

	void write(QJsonObject& json);
	void read(QJsonObject& json);
};