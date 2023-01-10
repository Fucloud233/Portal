#pragma once

#include "Matrix.h"
#include "Block.h"
#include "GraphicsBlockItem.h"

#include <QGraphicsItem>

class GraphicsBlockItem;

class Map {
private:
	Matrix<Block*> data;
	Matrix<GraphicsBlockItem*> items;
	//QList<QGraphicsItem*> itemsList;

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

	GraphicsBlockItem* getItem(int x, int y) const ;
	GraphicsBlockItem* getItem(const QPoint& point) const ;
	QList<GraphicsBlockItem*> getItems();
};
