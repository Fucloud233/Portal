#include "MapEditorWindow.h"

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

void MatrixTest() {
    Matrix<int> matrix(10, 10, 0);
    matrix.modify(1, 2, 3);
    qDebug() << matrix[1][2];
    system("pause");
}

int main(int argc, char *argv[])
{
    //MatrixTest();
    //return 0;

    QApplication a(argc, argv);
    MapEditorWindow w;
    w.show();
    
    return a.exec();

    OperatorTest();

    return 0;
}
