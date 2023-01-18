#include "GraphicsItem.h"

int GraphicsItem::blockSize = -1;

GraphicsItem::GraphicsItem() :
	QGraphicsItem(nullptr) {
}

void GraphicsItem::setHeight(Height height) {
	setZValue(height);
}

void GraphicsItem::setBlockSize(int size) {
	blockSize = size;
}