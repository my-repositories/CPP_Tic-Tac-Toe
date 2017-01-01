#ifndef GAME_WIN_H
#define GAME_WIN_H

#include "Ui.h"

class Game : public Ui
{
public:
    Game();
    ~Game();
    void Start();

private:
    void RestartGame(char *message);
    void GetStep(int &y, int &x);
    void Display();
};

#endif // !GAME_WIN_H
