#ifndef UI_H
#define UI_H

#include "board.h"

class Ui
{
public:
    Ui();
    virtual ~Ui();
    virtual void Start() = 0;

protected:
    bool m_game_state;
    int m_player_step, y, x;
    Board *m_board;

    void Update();
    void Move();
    virtual void RestartGame(char *message) = 0;
    virtual void GetStep(int &y, int &x) = 0;
    virtual void Display() = 0;
};

#endif // !UI_H