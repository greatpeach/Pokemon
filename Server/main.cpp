#include <QCoreApplication>
#include <myserver.h>
#include <Windows.h>
#include <time.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(NULL));
    myserver *myserver_ = new myserver;

    return a.exec();
}
