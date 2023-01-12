#include "MainWindow.h"

#include <QGraphicsItem>
#include <QStringList>
#include <QStringListModel>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setupGraphics();
    setupOperator();
    setWindowTitle("Map Editor");
}

MainWindow::~MainWindow()
{}

void MainWindow::setupGraphics() {
    // [Map] 将地图信息显示载入窗体
    mapView = new MapGraphicsView(&map, &Operator, this);
    connect(mapView, SIGNAL(selectBlock()), this, SLOT(updateStatus()));
    setCentralWidget(mapView);
}

void MainWindow::setupOperator() {

    // [blockSelect] 
    QListView* listView = new QListView();
    listView->setModel(Operator.getInfoModel());
    listView->setDragDropMode(QAbstractItemView::DragOnly);

    QDockWidget* blockSelect = new QDockWidget("方块选择", this);
    blockSelect->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockSelect->setBaseSize(100, height());
    blockSelect->setWidget(listView);

    addDockWidget(Qt::LeftDockWidgetArea, blockSelect);

    // [BlockStatus] 
    statusView = new BlockStatusView;
    // 当Status changed, update mapView
    connect(statusView, SIGNAL(statusChanged()), mapView, SLOT(updateBlock()));

    QDockWidget* blockStatus = new QDockWidget("方块状态", this);
    blockStatus->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    blockStatus->setBaseSize(100, height());
    blockStatus->setWidget(statusView);

    addDockWidget(Qt::LeftDockWidgetArea, blockStatus);
}

void MainWindow::updateStatus() {
    //qDebug() << map.getSelectedPos().x() << map.getSelectedPos().y();
    if (!map.isNULL(map.getSelectedPos())) {
        statusView->updateStatus(map.SelectedBlockStatus());
    }
    //qDebug() << point.x() << point.y();
}