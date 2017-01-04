#include "../include/settings.h"

#if MY_GAME == CONSOLE_GAME
#include "../include/game_con.h"

#elif MY_GAME == QT_GAME
#include "../include/game_qt.h"
#endif

#if MY_GAME != QT_GAME

int main(int argc, char *argv[])
{
    Game game;
    game.Start();
    return 0;
}

#else

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game game;
    game.Start();

    return app.exec();
}

#endif
