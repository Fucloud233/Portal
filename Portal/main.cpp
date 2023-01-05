#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include "Block.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();

    Block block("Empty", Block::FLOOR);
    block.saveInfo();
    
    system("pause");
    return 0;
}
