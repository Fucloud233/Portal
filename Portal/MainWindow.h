#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include "Map.h"
#include "BlockInfoOperator.h"
#include "MapGraphicsView.h"
#include "BlockStatusView.h"

#include <QListView>
#include <QMouseEvent>
#include <QMdiArea>
#include <QMdiSubWindow>


// http://shouce.jb51.net/qt-beginning/15.html

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    
    BlockStatusView* statusView;

    QMdiArea* mdiArea;
    QMdiSubWindow* currentWindow;

    void setupMdiArea();
    void setupOperator();
    void setupMenu();
    void setupGraphics(bool isNew, QString FilePath = QString());

private slots:
    void openMap();
    void saveMap();
    void saveAsMap();
    void newMap();
};
