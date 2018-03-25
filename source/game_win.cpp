#include "settings.h"
#if MY_GAME == WIN_GAME \
    && !defined(__CYGWIN__) \
    && (defined(WIN32) || defined(_WIN32) || defined(__WIN32))
#include "game_win.h"
#include <iostream>
#include <cstdlib>

Game::Game() : Ui()
{
    setlocale(LC_ALL, "Russian");

    int field_size = 3, win_streak = 3;
    std::cout << "������ ����: ";
    std::cin >> field_size;

    std::cout << "���������� �������� ���������: ";
    std::cin >> win_streak;

    m_board->SetFieldSize(field_size);
    m_board->SetWinStreak(win_streak);
}

void Game::Start()
{
    while (m_game_state)
    {
        Update();
    }
}

Game::~Game()
{
    delete m_board;
}

// ���������� ���� ������� ��� �����
void Game::RestartGame(char *message)
{
    std::cout << message << " ������� ������� ��� ���? 1/0: ";
    std::cin.ignore();
    if (std::getchar() == '0')
        m_game_state = false;
    else
    {
        m_player_step = 1;
        m_board->ClearBoard();
    }
}

// ������ ���� ������
void Game::GetStep(int &y, int &x)
{
    std::cout << "\n[����� " << m_player_step << "] ��� ��� (y; x): ";
    std::cin >> y >> x;
}

// ����������� �������� ����
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

#endif // !GAME_WIN_H
