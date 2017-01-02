#ifndef GAME_CON_H
#define GAME_CON_H

#include "Ui.h"

class Game : public Ui
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
