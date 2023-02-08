#pragma once

#include "GraphicsItem.h"
#include "BlockGameGraphicsItem.h"
#include "MapGame.h"

#include <QRectF>
#include <QList>
#include <QTimer>

class PlayerGraphicsItem : public GraphicsItem {
public:
	PlayerGraphicsItem();
	PlayerGraphicsItem(const QPoint& pos, MapGame* map);

	QPainterPath shape() const;
	int type() const override;

	void moveX(float step);
	void moveY(float step);
	void setDirect(qreal direct);
	qreal Direct() const;

	PlayerGraphicsItem* Copy();
	
private:
	MapGame* parentMap;
	
	PlayerGraphicsItem* copy_player;
	bool enter_flag;

	int R;
	qreal angle;

	void translatePos(QPoint& pos, Block::Side s_side, Block::Side t_side);
	void drawCopyPlayer(const QPoint& pos, bool isRed);

	bool checkcolliding();

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
