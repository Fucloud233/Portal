#pragma once

#include "GameGraphicsView.h"

#include <QMainWindow>

class GameWindow :public QMainWindow{
	Q_OBJECT
public:
	GameWindow(QWidget* parent = nullptr);
	~GameWindow();

private:
	GameGraphicsView* mapView;

	void test();
};

