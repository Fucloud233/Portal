#include "GameGraphicsView.h"

GameGraphicsView::GameGraphicsView(QWidget* parent) : 
	MapGraphicsView(parent) {
	map = new MapGame;

	// 让系统能够跟踪Mouse
	setMouseTracking(true);
}

void GameGraphicsView::addItems() {
	MapGraphicsView::addItems();

	player = new PlayerGraphicsItem(map->SpawnPos(), map->BlockSize());
	player->setZValue(10);
	scene->addItem(player);
}

bool GameGraphicsView::loadMap(QString filePath) {
	if (MapGraphicsView::loadMap(filePath)) {
		step = BlockSize / 48;

		keyRespondTimer = new QTimer(this);
		connect(keyRespondTimer, &QTimer::timeout, this, &GameGraphicsView::movePlayer);

		return true;
	}
	return false;
}

void GameGraphicsView::updateDirect() {
	QPointF playerPos = player->scenePos();
	qreal angle = qAtan2<qreal>(mousePos.y() - playerPos.y(), mousePos.x() - playerPos.x());
	player->setDirect(angle);
	player->update();
}

void GameGraphicsView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		BulletGraphicsItem* bullet = new BulletGraphicsItem(Qt::red, player->Direct(), 10, player->scenePos());
		bullet->setZValue(8);
		scene->addItem(bullet);
		
	}else if(event->button() == Qt::RightButton){
		BulletGraphicsItem* bullet = new BulletGraphicsItem(Qt::blue, player->Direct(), 10, player->scenePos());
		bullet->setZValue(8);
		scene->addItem(bullet);
	}
}

void GameGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	mousePos = mapToScene(event->pos());

	updateDirect();
}

void GameGraphicsView::keyPressEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) 
		keys.append(event->key());
	if (!keyRespondTimer->isActive()) 
		keyRespondTimer->start(4);
}

void GameGraphicsView::keyReleaseEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat())
		keys.removeAll(event->key());
	if (keys.isEmpty())
		keyRespondTimer->stop();
}

void GameGraphicsView::movePlayer() {
	updateDirect();

	for (int key : keys) {
		switch (key) {
		case Qt::Key_W:
			player->moveY(-step);
			break;
		case Qt::Key_A:
			player->moveX(-step);
			break;
		case Qt::Key_S:
			player->moveY(step);
			break;
		case Qt::Key_D:
			player->moveX(step);
			break;
		}
	}
}