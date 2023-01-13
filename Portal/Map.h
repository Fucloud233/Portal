#pragma once

#include "Matrix.h"
#include "Block.h"
#include "BlockStatus.h"
#include "BlockGraphicsItem.h"

#include <QGraphicsItem>

class BlockGraphicsItem;

class Map {
private:
	//Matrix<Block*> data;
	Matrix<BlockStatus> statuses;
	Matrix<BlockGraphicsItem*> items;

	QPoint selected_block_index;

	int blockSize;
	int width, height;

public:
	Map(int blockSize = 48);
	~Map();

	void initial(int width = 10, int height = 10);
	
	bool modify(int x, int y, int blockCode, BlockStatus* status = NULL);
	bool modify(const QPoint& point, int blockCode, BlockStatus* status = NULL);
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
	BlockStatus* SelectedBlockStatus() const;
	
	BlockStatus* getBlockStatus(const QPoint& point) const;
	BlockStatus* getBlockStatus(int x, int y) const;
	BlockGraphicsItem* getItem(const QPoint& point) const;
	BlockGraphicsItem* getItem(int x, int y) const ;
	QList<BlockGraphicsItem*> getItems();

	// 文件处理
	void write(QJsonObject& json);
	void read(QJsonObject& json);
};
