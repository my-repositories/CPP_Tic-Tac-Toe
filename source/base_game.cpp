#include "../include/base_game.h"

BaseGame::BaseGame()
{
    m_count_win_x = m_count_win_o = 0;
    m_game_state = true;
    m_player_step = 1;
    m_board = new Board();
}

BaseGame::~BaseGame()
{
    delete m_board;
}

// Get game state ( DRAW | X_WIN | O_WIN | NEXT_STEP )
void BaseGame::Update()
{
    char* message;

    switch (m_board->GameOver())
    {
    case Board::STATE_DRAW:
        message = (char*)"It's a tie!";
        break;
    case Board::STATE_X_WINNER:
        message = (char*)"X wins!";
        ++m_count_win_x;
        break;
    case Board::STATE_O_WINNER:
        message = (char*)"O wins!";
        ++m_count_win_o;
        break;
    default:
        return;
    }
    
    m_game_state = false;
    RestartGame(message);
}

// Handle step
void BaseGame::Move()
{
    if (m_player_step == 1)
    {
        if (m_board->SetCell(m_y, m_x, Board::CELL_X))
            m_player_step = 2;
    }
    else
    {
        if (m_board->SetCell(m_y, m_x, Board::CELL_O))
            m_player_step = 1;
    }
}
