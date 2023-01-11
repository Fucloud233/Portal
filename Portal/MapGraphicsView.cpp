#include "MapGraphicsView.h"

int MapGraphicsView::BlockSize = 48;

MapGraphicsView::MapGraphicsView(Map* map, BlockInfoOperator* Operator, QWidget* parent)
    : QGraphicsView(parent) {

    this->Operator = Operator;
    this->map = map;
    map->initial(BlockSize);

    // initial the scence
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    setScene(scene);

    // [HighLight]
    highlightArea = new BlockGraphicsItem(map);
    highlightArea->setZValue(6);
    highlightArea->setVisible(false);
    scene->addItem(highlightArea);

    // [Block]
    intial();
    //testPaint();
}

void MapGraphicsView::intial() {

    const QList<BlockGraphicsItem*>& items = map->getItems();

    for (BlockGraphicsItem* item : items) {
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
    // 将坐标进行转换
    QPoint p = mapToScene(event->pos()).toPoint();
    if (!map->translatePos(p)) {
        highlightArea->setVisible(false);
        return;
    }

    QByteArray blockData = event->mimeData()->imageData().toByteArray();
    QDataStream dataStream(&blockData, QIODevice::ReadOnly);
    QPixmap img;
    dataStream >> img;

    highlightArea->setImg(img);
    highlightArea->setPos(p);
    //qDebug() << highlightArea->pos().x() << highlightArea->pos().y();
    highlightArea->setVisible(true);
}

void MapGraphicsView::dropEvent(QDropEvent* event) {
    // 将坐标进行转换
    QPoint p = mapToScene(event->pos()).toPoint();
    if (map->translatePos(p)) {
        // 得到编号
        int blockCode = event->mimeData()->text().toInt();

        scene->removeItem(map->getItem(p));
        map->modify(p, Operator->value(blockCode));
        scene->addItem(map->getItem(p));
    }

    highlightArea->setVisible(false);
}

void MapGraphicsView::mousePressEvent(QMouseEvent* event) {
    // 注意事件和信号的传递顺序
    QGraphicsView::mousePressEvent(event);
    selectBlock();
}