#include "GameWindow.h"


GameWindow::GameWindow(QWidget* parent) :
    QMainWindow(parent) {
    // 设置基本属性
    setWindowTitle("Map Editor");
    setMinimumSize(1280, 720);
    resize(minimumSize());
}