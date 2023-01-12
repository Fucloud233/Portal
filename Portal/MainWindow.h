#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include "Map.h"
#include "BlockInfoOperator.h"
#include "MapGraphicsView.h"
#include "BlockStatusView.h"

#include <QListView>
#include <QMouseEvent>


// http://shouce.jb51.net/qt-beginning/15.html

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    
    Map map;
    BlockInfoOperator Operator;
    
    BlockStatusView* statusView;
    MapGraphicsView* mapView;

    void setupGraphics();
    void setupOperator();

private slots:
    void updateStatus();
};
