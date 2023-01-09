#include "MainWindow.h"

#include <QGraphicsItem>
#include <QStringList>
#include <QStringListModel>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setupView();
    setWindowTitle("Map Editor");
}

MainWindow::~MainWindow()
{}

void MainWindow::setupView() {

    // [Block] 将方块信息载入窗体
    listView = new QListView();
    listView->setModel(Operator.getInfoItems());

    //listView->setViewMode(QListView::IconMode);
    listView->setMaximumWidth(120);
    listView->setDragEnabled(true);


    // [Map] 将地图信息显示载入窗体
    map.initial();
    mapView = new MapGraphicsView(&map);

    //QGraphicsScene* scene = new QGraphicsScene();
    //scene->setBackgroundBrush(Qt::black);
    //mapView->setScene(scene);
    
    
    // 创建布局
    QFrame* frame = new QFrame();
    QHBoxLayout* frameLayout = new QHBoxLayout(frame);
    frameLayout->addWidget(listView);
    frameLayout->addWidget(mapView);
    this->setCentralWidget(frame);
}

//void MainWindow::paint() {
//    // 创建容器
//    QGraphicsScene* scene = new QGraphicsScene();
//    scene->setBackgroundBrush(Qt::black);
//
//    const QList<QGraphicsItem*>& items = map.getItems();
//    for (QGraphicsItem* item : items) {
//        scene->addItem(item);
//    }
//    ui.MainGraphicsView->setAcceptDrops(true);
//    ui.MainGraphicsView->setScene(scene);
//}

//void MainWindow::dropEvent(QDropEvent* event) {
//    qDebug() << "drop";
//}

//void MainWindow::mousePressEvent(QMouseEvent* event) {
//    qDebug() << "press";
//}
