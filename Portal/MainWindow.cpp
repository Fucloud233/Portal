#include "MainWindow.h"

#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //testPaint();
}

MainWindow::~MainWindow()
{}


// 测试函数 生成5x5的矩阵
void MainWindow::testPaint() {
    // 创建容器
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);

    // 创建矩阵 并添加
    int len = 5;
    int width = 40, height = 40;
    QGraphicsRectItem*** rects;
    rects = new QGraphicsRectItem * *[len];
    for (int i = 0; i < len; i++) {
        rects[i] = new QGraphicsRectItem * [len];
        for (int j = 0; j < len; j++) {
            rects[i][j] = new QGraphicsRectItem();
            rects[i][j]->setRect(i * width, j * height, width, height);
            rects[i][j]->setBrush(Qt::gray);
            rects[i][j]->setFlag(QGraphicsItem::ItemIsMovable);
            scene->addItem(rects[i][j]);
        }
    }
    ui.graphicsView->setScene(scene);
}
