#include "settings.h"

#if MY_GAME == CONSOLE_GAME
#include "game_con.h"
#include <iostream>
#include <cstdlib>

Game::Game() : Ui()
{
    setlocale(LC_ALL, "Russian");

    int field_size = 3, win_streak = 3;
    std::cout << "Размер поля: ";
    std::cin >> field_size;

    std::cout << "Количество соседних элементов: ";
    std::cin >> win_streak;

    m_board->SetFieldSize(field_size);
    m_board->SetWinStreak(win_streak);
}

Game::~Game(){}

void Game::Start()
{
    while (m_game_state)
    {
        Update();
    }
}

// Продолжить игру сначала или выйти
void Game::RestartGame(char *message)
{
    std::cout << message << " Желаете сыграть еще раз? 1/0: ";
    std::cin.ignore();
    if (std::getchar() == '0')
        m_game_state = false;
    else
    {
        m_player_step = 1;
        m_board->ClearBoard();
    }
}

// Запрос хода игрока
void Game::GetStep(int &y, int &x)
{
    std::cout << "\n[Игрок " << m_player_step << "] Ваш ход (y; x): ";
    std::cin >> y >> x;
}

// Отображение игрового поля
void Game::Display()
{
    std::system("cls||clear");

    int size = m_board->GetSize();
    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            switch (m_board->GetCell(x, y))
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
