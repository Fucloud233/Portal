#pragma once

#include <QGraphicsItem>

class GraphicsItem : public QGraphicsItem {
public:
	enum Height {
		DRAFT = 0, BOTTOM = 1, ON = 2, SELECTED = 3, TOP = 4
	};

	GraphicsItem(int blockSize = 1);

	void setPos(const QPoint& point);
	void setPos(int x, int y);
	void setX(int x);
	void setY(int y);

	virtual void setHeight(Height height);

	QPoint getPos() const;
	int x() const;
	int y() const;

	virtual bool isAccessible() const = 0;

protected:
	int blockSize;
	// 记录相对坐标
	QPoint index;
};