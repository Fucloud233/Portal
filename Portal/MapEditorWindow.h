#pragma once

#include <QtWidgets/QMainWindow>

#include "MapEdit.h"
#include "BlockInfoOperator.h"
#include "MapEditorGraphicsView.h"
#include "BlockStatusView.h"

#include <QListView>
#include <QMouseEvent>
#include <QMdiArea>
#include <QMdiSubWindow>

class MapEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    MapEditorWindow(QWidget *parent = nullptr);
    ~MapEditorWindow();

private:
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
