#include "maindesk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("开始游戏");
    w.show();
    return a.exec();
}
