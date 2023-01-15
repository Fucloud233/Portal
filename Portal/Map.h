#pragma once

#include "Matrix.h"
#include "Block.h"
#include "BlockStatus.h"
#include "BlockGraphicsItem.h"
#include "BlockInfoOperator.h"

#include <QGraphicsItem>

#define ICON_SIZE 48

class BlockGraphicsItem;

class Map {
protected:
	//Matrix<Block*> data;
	Matrix<BlockStatus*> blocks;
	Matrix<BlockGraphicsItem*> items;

	int blockSize;
	int width, height;

public:
	// 构造函数 默认
	Map();
	// 构造函数 初始化
	Map(int width, int height, int blockSize);
	~Map();

	virtual void initial(int width, int height, int blockSize);

	virtual bool modify(int x, int y, BlockStatus* status);
	virtual bool modify(const QPoint& point, BlockStatus* status);

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
	void read(const QJsonObject& json);
};