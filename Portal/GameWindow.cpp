#include "GameWindow.h"


GameWindow::GameWindow(QWidget* parent) :
    QMainWindow(parent) {
    // 设置基本属性
    setWindowTitle("Map Editor");
    setMinimumSize(1280, 720);
    resize(minimumSize());

    // 对Block操作类的初始化
    BlockInfoOperator::initial();
    GraphicsItem::setBlockSize(48);

    test();
}

GameWindow::~GameWindow() {
    BlockInfoOperator::saveBlocks();
}

void GameWindow::test() {
    mapView = new GameGraphicsView();
    mapView->loadMap("./Map/Map.map");
    setCentralWidget(mapView);
}