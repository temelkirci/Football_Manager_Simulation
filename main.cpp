#include "creategame.h"
#include "gamemenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QApplication a(argc, argv);

    GameMenu pGameMenu;
    pGameMenu.show();

    return a.exec();
}
