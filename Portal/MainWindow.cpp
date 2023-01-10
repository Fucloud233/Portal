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
    listView->setModel(Operator.getInfoModel());

    //listView->setMinimumSize(120, height());
    listView->setDragDropMode(QAbstractItemView::DragOnly);

    QDockWidget* blockSelect = new QDockWidget("方块选择", this);
    blockSelect->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockSelect->setBaseSize(100, height());
    blockSelect->setWidget(listView);

    // [Map] 将地图信息显示载入窗体
    mapView = new MapGraphicsView(&map, &Operator);

    QDockWidget* blockStatus = new QDockWidget("方块状态", this);
    blockSelect->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockSelect->setBaseSize(100, height());
    //blockSelect->setWidget();

    // 创建布局
    QFrame* frame = new QFrame();
    QHBoxLayout* frameLayout = new QHBoxLayout(frame);
    frameLayout->addWidget(mapView);
    this->setCentralWidget(frame);
    
    this->addDockWidget(Qt::LeftDockWidgetArea, blockSelect);
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
