#include "game_qt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.Start();

    return a.exec();
}
