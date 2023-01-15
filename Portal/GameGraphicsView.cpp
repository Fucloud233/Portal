#include "GameGraphicsView.h"

GameGraphicsView::GameGraphicsView(QWidget* parent) : 
	MapGraphicsView(parent) {
	map = new MapGame;
}