#pragma once

#include "Matrix.h"
#include "Block.h"
#include <QGraphicsItem>

class Map {
private:
	static int BlockSize;
	Matrix<Block> data;

public:
	Map();

	void initial();
	QList<QGraphicsItem*> getItems();
};