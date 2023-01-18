#pragma once

#include "GraphicsItem.h"
#include "MapGame.h"

#include <QRectF>
#include <QList>
#include <QTimer>

class PlayerGraphicsItem : public GraphicsItem {
public:
	PlayerGraphicsItem(const QPoint& pos = QPoint(0, 0), MapGame* map = NULL);

	QPainterPath shape() const;
	int type() const override;

	void moveX(float step);
	void moveY(float step);
	void setDirect(qreal direct);
	qreal Direct() const;

private:
	MapGame* parentMap;

	int R;
	qreal angle;

	bool checkcolliding();

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
