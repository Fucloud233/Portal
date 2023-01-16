#include "MapGraphicsView.h"

int MapGraphicsView::BlockSize = 48;

MapGraphicsView::MapGraphicsView(QWidget* parent) :
	QGraphicsView(parent) {

    // [注意] 指针需要初始化
    map = NULL;
    setEnabled(false);

    // initial the scence
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    setScene(scene);

    // 设置不产生拖影    
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

bool MapGraphicsView::loadMap(QString filePath) {
    // 1. 打开文件 解析Json
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("[Error] 文件打开失败!");
        return false;
    }

    QByteArray loadData = loadFile.readAll();
    QJsonObject json = (QJsonDocument::fromJson(loadData)).object();

    // 2. 利用Map的read函数读取
    map->read(json);

    // 3. 对Scene进行操作
    setEnabled(true);
    addItems();

    return true;
}

bool MapGraphicsView::saveMap(QString filePath) {
    QJsonObject json;

    map->write(json);

    // 处理文件保存
    QString path = filePath.left(filePath.lastIndexOf('/'));
    // 当路径不存在时 创建路径
    if (!QFile::exists(filePath)) {
        QDir dir(path);
        // 路径不存在-> 创造路径-> Error
        if (!dir.exists() && !dir.mkdir(path)) {
            return false;
        }
    }

    QFile saveFile(filePath);
    if (saveFile.open(QIODevice::WriteOnly)) {
        //qWarning("文件打开失败!");
        saveFile.write(QJsonDocument(json).toJson());
    }

    return true;
}

void MapGraphicsView::addItems() {
	const QList<BlockGraphicsItem*>& items = map->getItems();

	for (BlockGraphicsItem* item : items) {
        scene->addItem(item);
	}

    // 设置边界大小
    scene->setSceneRect(QRectF(0, 0, map->Width()*BlockSize, map->Height() * BlockSize));
}