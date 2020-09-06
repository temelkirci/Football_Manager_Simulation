#include "GameMenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));

    QApplication a(argc, argv);

    GameMenu pGameMenu;
    pGameMenu.show();

    return a.exec();
}
