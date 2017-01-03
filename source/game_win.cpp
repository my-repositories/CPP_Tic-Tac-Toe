#include "settings.h"
#if MY_GAME == WIN_GAME \
    && !defined(__CYGWIN__) \
    && (defined(WIN32) || defined(_WIN32) || defined(__WIN32))
#include "game_win.h"
#endif // !WIN_GAME
