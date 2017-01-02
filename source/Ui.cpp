#include "game_con.h"

Ui::Ui()
{
    m_game_state = true;
    m_player_step = 1;
    m_board = new Board();
}

Ui::~Ui()
{
    delete m_board;
}

// Определение состояния игры: ничья/победа/следующий ход
void Ui::Update()
{
    char* message;

    switch (m_board->GameOver())
    {
    case Board::STATE_DRAW:
        message = "Ничья!";
        break;
    case Board::STATE_X_WINNER:
        message = "Крестики победили!";
        break;
    case Board::STATE_O_WINNER:
        message = "Нолики победили!";
        break;
    default:
        return;
    }
    
    RestartGame(message);
}

// Осуществление хода игроком
void Ui::Move()
{
    // Ход первого игрока
    // И если ход выполнен
    // То ход передается второму игроку
    // Иначе игрок будет вводить данные до тех пор, пока они не будут корректны
    if (m_player_step == 1)
    {
        if (m_board->SetCell(y - 1, x - 1, Board::CELL_X))
            m_player_step = 2;
    }
    else
    {
        if (m_board->SetCell(y - 1, x - 1, Board::CELL_O))
            m_player_step = 1;
    }
}
