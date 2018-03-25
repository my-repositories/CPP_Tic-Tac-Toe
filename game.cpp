#include "game.h"
#include <iostream>
#include <cstdlib>

Game::Game()
{
    setlocale(LC_ALL, "Russian");

    int field_size = 3, win_streak = 3;
    std::cout << "������ ����: ";
    std::cin >> field_size;

    std::cout << "���������� �������� ���������: ";
    std::cin >> win_streak;

    if (field_size < 2 || field_size > 20 || win_streak < 2 || win_streak > 20)
    {
        field_size = 3;
        win_streak = 3;
    }

    game_state = true;
    player_step = 1;
    board = new Board(field_size, win_streak);
}

Game::~Game()
{
    delete board;
}

void Game::Start()
{
    while (game_state)
    {
        Update();
    }
}

// ����������� ��������� ����: �����/������/��������� ���
void Game::Update()
{
    char* message;

    Display();
    switch (board->GameOver())
    {
    case Board::STATE_DRAW:
        message = "�����!";
        break;
    case Board::STATE_X_WINNER:
        message = "�������� ��������!";
        break;
    case Board::STATE_O_WINNER:
        message = "������ ��������!";
        break;
    default:
        Move();
        return;
    }

    std::cout << message << " ������� ������� ��� ���? 1/0: ";
    std::cin.ignore();
    if(std::getchar() == '0')
        game_state = false;
    else
    {
        player_step = 1;
        board->ClearBoard();
    }
}

// ������������� ���� �������
void Game::Move()
{
    std::cout << "\n[����� " << player_step << "] ��� ��� (y; x): ";
    std::cin >> y >> x;

    // ��� ������� ������
    // � ���� ��� ��������
    // �� ��� ���������� ������� ������
    // ����� ����� ����� ������� ������ �� ��� ���, ���� ��� �� ����� ���������
    if (player_step == 1)
    {
        if (board->SetCell(y - 1, x - 1, Board::CELL_X))
            player_step = 2;
    }
    else
    {
        if (board->SetCell(y - 1, x - 1, Board::CELL_O))
            player_step = 1;
    }
}

// ����������� �������� ����
void Game::Display()
{
    std::system("cls||clear");

    int size = board->GetSize();
    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            switch (board->GetCell(x, y))
            {
            case Board::CELL_X: std::cout << "X "; break;
            case Board::CELL_O: std::cout << "O "; break;
            default: std::cout << "- "; break;
            }
        }
        std::cout << std::endl;
    }
}
