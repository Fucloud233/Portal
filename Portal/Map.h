#pragma once

#include "Matrix.h"
#include "Block.h"
#include <QGraphicsItem>

class Map {
private:
	Matrix<Block> data;

public:
	Map();

	void initial();

	bool checkPos(int x, int y) const;
	QList<QGraphicsItem*> getItems(int BlockSize = 32);

};