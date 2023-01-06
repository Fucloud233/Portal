#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "BlockInfoOperator.h"
#include "Block.h"

void blockTest() {
    Block block("Empty", Block::FLOOR);
    block.saveInfo();

    system("pause");
}

void OperatorTest() {
    BlockInfoOperator op;

    system("pause");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();

    OperatorTest();

    return 0;
}
