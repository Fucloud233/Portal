#pragma once

#include <QGraphicsItem>

class GraphicsItem : public QGraphicsItem {
public:
	enum Height {
		DRAFT = 0, BOTTOM = 1, ON = 2, SELECTED = 3, TOP = 4
	};

	enum ElemType {
		PLAYER = UserType + 1,
		BULLET = UserType + 2,
		UNPASSABLE = UserType + 3,
		PASSABLE = UserType + 4,
	};

	GraphicsItem();

	virtual void setHeight(Height height);

	virtual int type() const = 0;

	static void setBlockSize(int blockSize);

protected:
	static int blockSize;
};