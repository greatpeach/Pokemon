#include "mainwindow.h"
#include <QApplication>
#include <myserver.h>
#include <QObject>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainWindow main_window;

    return a.exec();
}
