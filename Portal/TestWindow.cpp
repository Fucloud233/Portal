#include "TestWindow.h"

#include "MapEditorGraphicsView.h"

TestWindow::TestWindow(QWidget* parent) :
	QMainWindow(parent) {

	resize(1280, 720);

	MapEditorGraphicsView* mapView = new MapEditorGraphicsView(this);
	setCentralWidget(mapView);
}