#pragma once

#include "Map.h"

class MapGame : public Map {
public:
	MapGame();

	bool modify(int x, int y, BlockStatus* status);

	bool canTeleport();
	bool canEnter(const QPoint& pos, Block::Side side, bool isRed);

	QPoint RedDoorPos() const;
	QPoint BlueDoorPos() const;
	Block::Side RedDoorSide() const;
	Block::Side BlueDoorSide() const;

private:
	QPointF current_pos;
	QPoint red_pos;
	Block::Side red_side;
	QPoint blue_pos;
	Block::Side blue_side;

	inline bool checkPoint(const QPoint& pos) const ;

	void read(const QJsonObject& json) override;

public slots:
	void openDoor(QPoint pos, Block::Side side, bool isRed);
};