#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
public:
    Game();
    ~Game();
    void Start();

private:
    bool game_state;
    int player_step, x, y;
    Board *board;

    void Update();
    void Move();
    void Display();
};

#endif // !GAME_H
