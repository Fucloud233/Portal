#pragma once

#include "Matrix.h"
#include "Block.h"
#include <QGraphicsItem>

class Map {
private:
	Matrix<Block*> data;
	Matrix<QGraphicsItem*> items;
	//QList<QGraphicsItem*> itemsList;

	int BlockSize;

public:
	Map();
	~Map();

	void initial(int BlockSize);
	
	bool modify(int x, int y, Block* block);
	
	QGraphicsItem* getItem(int x, int y);

	bool checkPos(int x, int y) const;
	QList<QGraphicsItem*> getItems();

	
};