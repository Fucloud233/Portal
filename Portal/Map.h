#pragma once

#include "Matrix.h"
#include "Block.h"

#include <QGraphicsItem>


class Map {
private:
	Matrix<Block*> data;
	Matrix<QGraphicsItem*> items;
	//QList<QGraphicsItem*> itemsList;

	int blockSize;

public:
	Map();
	~Map();

	void initial(int blockSize);
	
	bool modify(int x, int y, Block* block);
	bool modify(const QPoint& point, Block* block);

	bool translatePos(QPoint& point) const ;

	bool checkPos(int x, int y) const;
	bool checkPos(const QPoint& point) const;

	int BlockSize() const ;

	QGraphicsItem* getItem(int x, int y);
	QGraphicsItem* getItem(const QPoint& point);
	QList<QGraphicsItem*> getItems();
};
