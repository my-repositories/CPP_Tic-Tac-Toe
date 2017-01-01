// CONSOLE (iostream + cstdlib)
#define CONSOLE_GAME 0

// QT (Cross-platform application framework)
#define QT_GAME 1

// WIN (Windows.h || gtk.h)
#define WIN_GAME 2

// Choose Your Destiny
#define MY_GAME CON_GAME

#if MY_GAME == CONSOLE_GAME
#include "game_con.h"
#elif MY_GAME == QT_GAME
#include "game_qt.h"
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "game_win.h"
#else
#include "game_gtk.h"
#endif

int main(int argc, char *argv[])
{
    Game game;
    game.Start();
    return 0;
}
