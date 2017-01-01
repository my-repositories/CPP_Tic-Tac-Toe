#define CONSOLE_GAME 1

#if CONSOLE_GAME == 1
#include "game_con.h"
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
