#include "MapGraphicsView.h"

int MapGraphicsView::BlockSize = 32;

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
    highlightArea = new QGraphicsPixmapItem();
    highlightArea->setVisible(false);
    scene->addItem(highlightArea);

    // [Block]
    intial();
    //setAcceptDrops(true);
    //testPaint();
}

void MapGraphicsView::intial() {
    const QList<QGraphicsItem*>& items = map->getItems();

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
    QPointF p = this->mapToScene(event->pos());
    int x = p.x() / BlockSize, y = p.y() / BlockSize;

    if (!map->checkPos(x, y)) {
        highlightArea->setVisible(false);
        return;
    }

    //qDebug() << x<<y;
    QByteArray blockData = event->mimeData()->imageData().toByteArray();
    QDataStream dataStream(&blockData, QIODevice::ReadOnly);
    QPixmap img;
    dataStream >> img;


    highlightArea->setPixmap(img);
    highlightArea->setScale(BlockSize/img.width());
    highlightArea->setPos(x * BlockSize, y * BlockSize);
    highlightArea->setVisible(true);
}


void MapGraphicsView::dropEvent(QDropEvent* event) {
    //QByteArray blockData = event->mimeData()->data("image/x-block-info");
    //QDataStream dataStream(&blockData, QIODevice::ReadOnly);
    //   
    //QVariant v;
    //dataStream >> v;
    //Block* block = v.value<Block*>();
        
    // 得到对应坐标
    int blockCode = event->mimeData()->text().toInt();

    QPointF p = this->mapToScene(event->pos());
    int x = p.x() / BlockSize, y = p.y() / BlockSize;

    if (map->modify(x, y, Operator->value(blockCode))) {
        scene->addItem(map->getItem(x, y));
    }

    highlightArea->setVisible(false);
}