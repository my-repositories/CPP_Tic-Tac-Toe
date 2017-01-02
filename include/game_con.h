#ifndef GAME_CON_H
#define GAME_CON_H

#include "Ui.h"

class Game : public Ui
{
public:
    Game();
    ~Game();
    void Start();

private:
    void SetOptions();
    void RestartGame(char *message);
    void GetStep(int &y, int &x);
    void Display();
};

#endif // !GAME_CON_H
