#include "MapEditorGraphicsView.h"

MapEditorGraphicsView::MapEditorGraphicsView(QWidget* parent):
    MapGraphicsView(parent) {

    highlightArea = NULL;
}

void MapEditorGraphicsView::intialMap() {
    map = new MapEdit(10, 10, BlockSize);
    setEnabled(true);
    addItems();
}

void MapEditorGraphicsView::addItems() {
    MapGraphicsView::addItems();

    // [HighLight]
    highlightArea = new BlockEditGraphicsItem((MapEdit*) map);
    highlightArea->setHeight(BlockGraphicsItem::TOP);
    highlightArea->setVisible(false); 
    scene->addItem(highlightArea);
}

// 测试函数 生成5x5的矩阵
void MapEditorGraphicsView::testPaint() {
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

void MapEditorGraphicsView::dragMoveEvent(QDragMoveEvent* event) {
    // 将坐标进行转换
    QPoint p = mapToScene(event->pos()).toPoint();
    // 当坐标不合法 或者此处非空 才离开
    if (!map->translatePos(p)) {
        highlightArea->setVisible(false);
        return;
    }
    //qDebug() << p.x() << p.y();

    int blockCode = event->mimeData()->text().toInt();

    highlightArea->setImg(BlockInfoOperator::value(blockCode)->BlockImg());
    highlightArea->setPos(p);
    //qDebug() << highlightArea->pos().x() << highlightArea->pos().y();
    highlightArea->setVisible(true);
}

void MapEditorGraphicsView::dropEvent(QDropEvent* event) {
    // 将坐标进行转换
    QPoint p = mapToScene(event->pos()).toPoint();

    // 只有当坐标合法 且当前位置不为空时 才可以放置
    if (map->translatePos(p)&&map->isNULL(p)) {
        scene->removeItem(map->getItem(p));
        // 修改方块
        int blockCode = event->mimeData()->text().toInt();
        map->modify(p, new BlockStatus(blockCode));
        scene->addItem(map->getItem(p));
    }

    highlightArea->setVisible(false);
}

void MapEditorGraphicsView::mousePressEvent(QMouseEvent* event) {
    // [注意] 注意事件和信号的传递顺序
    QGraphicsView::mousePressEvent(event);

    BlockStatus* status = ((MapEdit*)map)->SelectedBlockStatus();
    if (status && !status->isNULL()) {
        emit selectBlock(status);
    }
}

void MapEditorGraphicsView::updateBlock() {
    // 更新选中的方块
    ((MapEdit*)map)->getSelectedItem()->update();
}