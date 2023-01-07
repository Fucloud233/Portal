#include "MainWindow.h"

#include <QGraphicsItem>
#include <QStringList>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //testPaint();
    map.initial();

    // 绘制函数
    this->paint();
    this->initalBlockInfoList();
}

MainWindow::~MainWindow()
{}


void MainWindow::initalBlockInfoList() {
    //QStringListModel* namesModel = new QStringListModel(Operator.getNames());
    //ui.BlockInfoListView->setModel(namesModel);
    
    ui.BlockInfoListView->setModel(Operator.getInfoItems());
    ui.BlockInfoListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::paint() {
    // 创建容器
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);

    const QList<QGraphicsItem*>& items = map.getItems();
    for (QGraphicsItem* item : items) {
        scene->addItem(item);
    }

    ui.MainGraphicsView->setScene(scene);
}

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
    ui.MainGraphicsView->setScene(scene);
}
