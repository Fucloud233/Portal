#pragma once

#include "GameGraphicsView.h"

#include <QMainWindow>

class GameWindow :public QMainWindow{
	Q_OBJECT
public:
	GameWindow(QWidget* parent = nullptr);

private:
	GameGraphicsView* mapView;

	void test();
};

