#pragma once

#include "Map.h"

class MapGame : public Map {
public:
	MapGame();

private:
	QPointF current_pos;

	void read(const QJsonObject& json) override;
};