#ifndef GAME_CON_H
#define GAME_CON_H

#include "../include/base_game.h"

class Game : public BaseGame
{
public:
    explicit Game();
    ~Game();
    void Start() override;

private:
    void SetOptions() override;
    void RestartGame(char *message) override;
    void GetStep() override;
    void Display();
};

#endif // !GAME_CON_H
