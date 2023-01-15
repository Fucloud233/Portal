#include "MapEditorWindow.h"

#include <QGraphicsItem>
#include <QStringList>
#include <QStringListModel>
#include <QtWidgets>
#include <QSizePolicy>

MapEditorWindow::MapEditorWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 设置基本属性
    setWindowTitle("Map Editor");
    setMinimumSize(1280, 720);
    resize(minimumSize());

    // 对Block操作类的初始化
    BlockInfoOperator::initial();

    // 加载组件 
    setupMdiArea();
    setupOperator();
    setupMenu();
}

MapEditorWindow::~MapEditorWindow(){
}

void MapEditorWindow::setupMdiArea() {
    mdiArea = new QMdiArea;
    connect(mdiArea, &QMdiArea::subWindowActivated, [this](QMdiSubWindow* w) {
        currentWindow = w;
        });

    setCentralWidget(mdiArea);
}

void MapEditorWindow::setupOperator() {
    // [BlockSelect] 
    QListView* listView = new QListView();
    listView->setModel(BlockInfoOperator::getInfoModel());
    listView->setDragDropMode(QAbstractItemView::DragOnly);

    QDockWidget* blockSelect = new QDockWidget("方块选择", this);
    blockSelect->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockSelect->setBaseSize(100, height());
    blockSelect->setWidget(listView);

    // [BlockStatus] 
    statusView = new BlockStatusView;

    QDockWidget* blockStatus = new QDockWidget("方块状态", this);
    blockStatus->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockStatus->setBaseSize(100, height());
    blockStatus->setWidget(statusView);

    addDockWidget(Qt::LeftDockWidgetArea, blockSelect);
    addDockWidget(Qt::LeftDockWidgetArea, blockStatus);
}

void MapEditorWindow::setupMenu() {
    QMenu* fileMenu = menuBar()->addMenu("文件");
    QAction* newAction = new QAction("新建");
    QAction* saveAsAction = new QAction("另存为");
    QAction* openAction = new QAction("打开");

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    //fileMenu->addAction(saveAsAction);

    connect(newAction, SIGNAL(triggered()), SLOT(newMap()));
    connect(openAction, SIGNAL(triggered()), SLOT(openMap()));
    connect(saveAsAction, SIGNAL(triggered()), SLOT(saveAsMap()));
}

void MapEditorWindow::setupGraphics(bool isNew, QString filePath) {
    // [Map] 将地图信息显示载入窗体
    QMdiSubWindow* w = new QMdiSubWindow(mdiArea);
    MapEditorGraphicsView* mapView = new MapEditorGraphicsView(w);
    w->setWidget(mapView);
    w->showMaximized();
    
    // 创建文件时
    if (isNew) {
        w->setWindowTitle("NewMap.map");
        mapView->intialMap();
    }
    // 打开文件时
    else {
        // 截取文件名
        QString fileName = filePath.right(filePath.length() - filePath.lastIndexOf('/') - 1);
        w->setWindowTitle(fileName);
        mapView->loadMap(filePath);
    }

    // 当select block, update status view
    connect(mapView, SIGNAL(selectBlock(BlockStatus*)), statusView, SLOT(updateStatus(BlockStatus*)));
    // 当Status changed, update mapView
    connect(statusView, SIGNAL(statusChanged()), mapView, SLOT(updateBlock()));
}

void MapEditorWindow::saveMap() {

}

void MapEditorWindow::newMap() {
    setupGraphics(true);
}

void MapEditorWindow::saveAsMap() {

    MapEditorGraphicsView* mapView = qobject_cast<MapEditorGraphicsView*>(currentWindow->widget());

    // 打开文件Dialog 获取保存地址
    QFileDialog fileDialog;
    mapView->saveMap(fileDialog.getSaveFileName());
}

void MapEditorWindow::openMap() {
    // 打开文件Dialog 获取打开地址
    QFileDialog fileDialog;
    QString filePath = fileDialog.getOpenFileName();
    if(!filePath.isEmpty())
        setupGraphics(false, filePath);
}