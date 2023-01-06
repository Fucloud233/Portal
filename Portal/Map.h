#pragma once

#include "Matrix.h"
#include "Block.h"

#include <QList>
#include <QGraphicsItem>

class Map {
private:
	Matrix<Block> data;
	
	static int BlockSize;

public:
	Map();

	void initial();
	QList<QGraphicsItem*> getItems();
};