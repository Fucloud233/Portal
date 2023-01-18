#pragma once

#include "Map.h"

class MapGame : public Map {
public:
	MapGame();

	bool modify(int x, int y, BlockStatus* status);

	bool canTeleport();

	QPoint RedDoorPos() const;
	QPoint BlueDoorPos() const;
	BlockGraphicsItem::Side RedDoorSide() const;
	BlockGraphicsItem::Side BlueDoorSide() const;

private:
	QPointF current_pos;
	QPoint red_pos;
	BlockGraphicsItem::Side red_side;
	QPoint blue_pos;
	BlockGraphicsItem::Side blue_side;

	inline bool checkPoint(const QPoint& pos) const ;

	void read(const QJsonObject& json) override;

public slots:
	void openDoor(QPoint pos, BlockGraphicsItem::Side side, bool isRed);
};