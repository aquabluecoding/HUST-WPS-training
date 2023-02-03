#include "ksearcher.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KSearcher w;
    //引入了外部库QHotkey，用于实现全局热键
    QHotkey hotkey(QKeySequence("Alt+Space"), true);
    qDebug() << "Is registered:" << hotkey.isRegistered();
    QObject::connect(&hotkey, &QHotkey::activated, &w, &KSearcher::switchVisible);
    //w.show();
    return a.exec();
}
