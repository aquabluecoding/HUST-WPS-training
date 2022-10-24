#include "klottery.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KLottery w;
    w.show();
    return a.exec();
}
