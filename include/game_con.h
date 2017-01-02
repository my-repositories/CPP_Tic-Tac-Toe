#ifndef GAME_CON_H
#define GAME_CON_H

#include "Ui.h"

class Game : public Ui
{
public:
    explicit Game();
    ~Game();
    void Start(int &argc, char **argv);

private:
    void SetOptions();
    void RestartGame(char *message);
    void GetStep(int &y, int &x);
    void Display();
};

#endif // !GAME_CON_H
