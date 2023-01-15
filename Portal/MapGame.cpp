#include "MapGame.h"

MapGame::MapGame():
	Map() {

	current_pos = QPoint(0, 0);
}

void MapGame::read(const QJsonObject& json) {
	Map::read(json);

	current_pos = spawn_pos;
	//qDebug() << current_pos.x() << current_pos.y();
}