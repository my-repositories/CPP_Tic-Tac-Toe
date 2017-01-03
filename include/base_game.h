#ifndef BASE_GAME_H
#define BASE_GAME_H

#include "../include/board.h"

class BaseGame
{
public:
    explicit BaseGame();
    virtual ~BaseGame();
    virtual void Start() = 0;

protected:
    bool m_game_state;
    int m_player_step, m_y, m_x;
    Board *m_board;

    void Update();
    void Move();
    virtual void SetOptions() = 0;
    virtual void RestartGame(char *message) = 0;
    virtual void GetStep() = 0;
};

#endif // !BASE_GAME_H
