#include "MapGraphicsView.h"

int MapGraphicsView::BlockSize = 32;

MapGraphicsView::MapGraphicsView(Map* map, QWidget* parent)
    : QGraphicsView(parent) {
    this->map = map;

    // initial the scence
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    setScene(scene);

    // [HighLight]
    highlight_rect = new QGraphicsRectItem();
    highlight_rect->setVisible(false);
    scene->addItem(highlight_rect);

    // [Block]
    paint();
    //setAcceptDrops(true);
    //testPaint();
}

void MapGraphicsView::paint() {

    const QList<QGraphicsItem*>& items = map->getItems(BlockSize);
    for (QGraphicsItem* item : items) {
        scene->addItem(item);
    }

}

// 测试函数 生成5x5的矩阵
void MapGraphicsView::testPaint() {
    // 创建容器
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);

    // 创建矩阵 并添加
    //int len = 5;
    //int width = 40, height = 40;
    //QGraphicsRectItem*** rects;
    //rects = new QGraphicsRectItem * *[len];
    //for (int i = 0; i < len; i++) {
    //    rects[i] = new QGraphicsRectItem * [len];
    //    for (int j = 0; j < len; j++) {
    //        rects[i][j] = new QGraphicsRectItem();
    //        rects[i][j]->setRect(i * width, j * height, width, height);
    //        rects[i][j]->setBrush(Qt::gray);
    //        rects[i][j]->setFlag(QGraphicsItem::ItemIsMovable);
    //        scene->addItem(rects[i][j]);
    //    }
    //}

    setScene(scene);
}


void MapGraphicsView::dragMoveEvent(QDragMoveEvent* event) {
    highlight_rect->setVisible(true);

    QPointF p = this->mapToScene(event->pos());
    //qDebug() << p.x()<<p.y();
    int x = p.x() - int(p.x()) % BlockSize;
    int y = p.y() - int(p.y()) % BlockSize;

    highlight_rect->setRect(x, y, BlockSize, BlockSize);
    highlight_rect->setBrush(Qt::blue);
}