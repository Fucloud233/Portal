#include "MapGraphicsView.h"

#include "MapGame.h"
#include "PlayerGraphicsItem.h"
#include "BulletGraphicsItem.h"

#include <QEvent>

class GameGraphicsView: public MapGraphicsView {
	Q_OBJECT
public:
	GameGraphicsView(QWidget* parent = nullptr);

	bool loadMap(QString filePath) override;

private:
	// 用于存储连续按下的键
	QList<int> keys;
	QTimer* keyRespondTimer;

	PlayerGraphicsItem* player;
	float step;

	// 记录鼠标位置
	QPointF mousePos;

	void updateDirect();
	void enterDoor();

	void addItems() override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

private slots:
	void movePlayer();
};