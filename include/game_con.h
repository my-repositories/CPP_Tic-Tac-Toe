#ifndef GAME_CON_H
#define GAME_CON_H

#include "../include/base_game.h"

class Game : public BaseGame
{
public:
    explicit Game();
    ~Game();
    void Start();

private:
    void SetOptions();
    void RestartGame(char *message);
    void GetStep();
    void Display();
};

#endif // !GAME_CON_H
