#include "../include/settings.h"

#if MY_GAME == CONSOLE_GAME
#include "../include/game_con.h"
#include <iostream>
#include <cstdlib>

Game::Game() : BaseGame()
{
    SetOptions();
}

Game::~Game(){}

void Game::Start()
{
    while (m_game_state)
    {
        Display();
        GetStep();
        Move();
        Update();
    }
}

// Ask Game Settings (Field size & Win streak)
void Game::SetOptions()
{
    int field_size = 3, win_streak = 3;
    std::cout << "Field size: ";
    std::cin >> field_size;

    std::cout << "Win streak: ";
    std::cin >> win_streak;

    m_board->SetFieldSize(field_size);
    m_board->SetWinStreak(win_streak);
}

// Ask for Restart or Quit
void Game::RestartGame(char *message)
{
    Display();
    std::cout << message << " Play again? 1/0: ";
    std::cin.ignore();
    if (std::getchar() == '0')
        m_game_state = false;
    else
    {
        m_player_step = 1;
        m_board->ClearBoard();
    }
}

// Ask for player step
void Game::GetStep()
{
    std::cout << "\n[Player " << m_player_step << "] your step (y; x): ";
    std::cin >> m_y >> m_x;
    --m_y;
    --m_x;
}

// Display game table
void Game::Display()
{
    std::system("cls||clear");

    int size = m_board->GetSize();
    for (m_y = 0; m_y < size; m_y++)
    {
        for (m_x = 0; m_x < size; m_x++)
        {
            switch (m_board->GetCell(m_y, m_x))
            {
            case Board::CELL_X: std::cout << "X "; break;
            case Board::CELL_O: std::cout << "O "; break;
            default: std::cout << "- "; break;
            }
        }
        std::cout << std::endl;
    }
}

#endif // !GAME_CON_H
