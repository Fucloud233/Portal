#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include "Map.h"
#include "BlockInfoOperator.h"
#include "MapGraphicsView.h"

#include <QListView>


// http://shouce.jb51.net/qt-beginning/15.html

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;

    MapGraphicsView* mapView;
    QListView* listView;

    Map map;
    BlockInfoOperator Operator;
    
    void setupView();
    //void paint();
    //void testPaint();
    
private slots:
    //void dropEvent(QDropEvent* event);
    //void mousePressEvent(QMouseEvent* event);
};
