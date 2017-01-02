#include "settings.h"

#if MY_GAME == CONSOLE_GAME
#include "game_con.h"
#elif MY_GAME == QT_GAME
#include "game_qt.h"
#elif MY_GAME == SFML_GAME
#include "game_sfml.h"
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "game_win.h"
#else
#include "game_gtk.h"
#endif

int main(int argc, char *argv[])
{
    Game game;
    game.Start(argc, argv);
    return 0;
}
