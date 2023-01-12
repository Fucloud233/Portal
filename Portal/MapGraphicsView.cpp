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
    highlightArea->setHeight(BlockGraphicsItem::TOP);
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
    // 当坐标不合法 或者此处非空 才离开
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

    // 只有当坐标合法 且当前位置不为空时 才可以放置
    if (map->translatePos(p)||map->isNULL(p)) {

        scene->removeItem(map->getItem(p));
        // 修改方块
        int blockCode = event->mimeData()->text().toInt();
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

void MapGraphicsView::updateBlock() {
    // 更新选中的方块
    map->getItem(map->getSelectedPos())->update();
}