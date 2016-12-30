#include "game.h"
#include <iostream>
#include <cstdlib>

Game::Game()
{
    setlocale(LC_ALL, "Russian");

    int field_size = 3, win_streak = 3;
    std::cout << "Размер поля: ";
    std::cin >> field_size;

    std::cout << "Количество соседних элементов: ";
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

// Определение состояния игры: ничья/победа/следующий ход
void Game::Update()
{
    char* message;

    Display();
    switch (board->GameOver())
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
        Move();
        return;
    }

    std::cout << message << " Желаете сыграть еще раз? 1/0: ";
    std::cin.ignore();
    if(std::getchar() == '0')
        game_state = false;
    else
    {
        player_step = 1;
        board->ClearBoard();
    }
}

// Осуществление хода игроком
void Game::Move()
{
    std::cout << "\n[Игрок " << player_step << "] Ваш ход (y; x): ";
    std::cin >> y >> x;

    // Ход первого игрока
    // И если ход выполнен
    // То ход передается второму игроку
    // Иначе игрок будет вводить данные до тех пор, пока они не будут корректны
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

// Отображение игрового поля
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
