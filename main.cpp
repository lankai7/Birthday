#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow * w1=new MainWindow;
    w1->setWindowTitle("生日查询系统");
    w1->setWindowIcon(QIcon(":/res/img/WinUi.png"));
    w1->show();
    return a.exec();
}
