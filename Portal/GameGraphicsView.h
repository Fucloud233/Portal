#include "MapGraphicsView.h"

#include "MapGame.h"
#include "PlayerGraphicsItem.h"

#include <QEvent>

class GameGraphicsView: public MapGraphicsView {
	Q_OBJECT
public:
	GameGraphicsView(QWidget* parent = nullptr);

	bool loadMap(QString filePath) override;

private:
	// 用于存储连续暗
	QList<int> keys;
	QTimer* keyRespondTimer;

	PlayerGraphicsItem* player;
	float step;

	void addItems() override;

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

private slots:
	void movePlayer();
};