#include "GraphicsItem.h"

GraphicsItem::GraphicsItem(int blockSize) :
	QGraphicsItem(nullptr) {
	this->blockSize = blockSize;
}

void GraphicsItem::setHeight(Height height) {
	setZValue(height);
}