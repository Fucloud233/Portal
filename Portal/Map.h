#pragma once

#include "Matrix.h"
#include "Block.h"
#include "BlockStatus.h"
#include "BlockGraphicsItem.h"

#include <QGraphicsItem>

class BlockGraphicsItem;

class Map {
private:
	Matrix<Block*> data;
	Matrix<BlockStatus> statuses;

	Matrix<BlockGraphicsItem*> items;

	QPoint selected_block_index;

	int blockSize;

public:
	Map();
	~Map();

	void initial(int blockSize);
	
	bool modify(int x, int y, Block* block);
	bool modify(const QPoint& point, Block* block);
	bool swap(const QPoint& source, const QPoint& target);
	bool swap(int s_x, int s_y, int t_x, int t_y);

	bool translatePos(QPoint& point) const ;

	bool checkPos(int x, int y) const;
	bool checkPos(const QPoint& point) const;
	bool checkX(int x) const;
	bool checkY(int y) const;
	bool isNULL(const QPoint& point) const;

	int BlockSize() const ;

	// 设置选中的方块类型
	void setSelectedPos(const QPoint& point);
	QPoint getSelectedPos() const;
	bool hasSelected() const;
	Block* getSelectedBlock() const;
	BlockStatus* SelectedBlockStatus() const;

	Block* getBlock(const QPoint& point) const ;
	Block* getBlock(int x, int y) const ;
	BlockGraphicsItem* getItem(int x, int y) const ;
	BlockGraphicsItem* getItem(const QPoint& point) const ;
	QList<BlockGraphicsItem*> getItems();
};
