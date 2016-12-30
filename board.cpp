#include "board.h"

// Создание игрового поля NxN
Board::Board(const int field_size, const int win_streak)
    :
    FIELD_SIZE(field_size),
    WIN_STREAK(win_streak),
    board(field_size, std::vector<char>(field_size))
{}

// Очищение игрвого поля
void Board::ClearBoard() const
{
    for (int y = 0; y < FIELD_SIZE; y++)
        for (int x = 0; x < FIELD_SIZE; x++)
            board[y][x] = CELL_EMPTY;
}

// Определение конца игры
char Board::GameOver() const
{
    char state;

    // Проверка на ничью
    state = CheckDraw();
    if (state == STATE_DRAW)
        return STATE_DRAW;

    // Массив функций с проверками на победу
    static char(Board::*checks[])(char) const =
    {
        &Board::CheckAntiDiagonal,
        &Board::CheckDiagonal,
        &Board::CheckVertical,
        &Board::CheckHorizontal
    };

    // Проход по массиву функций
    for (int i = 0; i < 4; i++)
    {
        state = CheckWin(this, checks[i]);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    return STATE_NEXT_STEP;
}

// Обработка хода игрока
bool Board::SetCell(int x, int y, char player) const
{
    // Валидация координат
    if (x < 0 || y < 0 || x >= FIELD_SIZE || y >= FIELD_SIZE)
        return false;

    // Если ячейка занята
    if (board[x][y] == CELL_O || board[x][y] == CELL_X)
        return false;

    board[x][y] = player;
    return true;
}

// Определение ничьей
char Board::CheckDraw() const
{
    // Ищем хотя бы 1 пустую ячейку
    for (int y = 0; y < FIELD_SIZE; y++)
    {
        for (int x = 0; x < FIELD_SIZE; x++)
        {
            if (board[y][x] == 0)
                return STATE_NEXT_STEP;
        }
    }

    return STATE_DRAW;
}

// Определение победителя
char Board::CheckWin(const Board *board, char(Board::*pCheck)(char) const) const
{
    char state;

    // Проход по полю первым игроком (player = 1)
    // Затем вторым игроком (player = 2)
    for (int player = 1; player < 3; player++)
    {
        state = (board->*pCheck)(player);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    return STATE_NEXT_STEP;
}

// Проход по побочной диагонали
char Board::CheckAntiDiagonal(char player) const
{
    int streak_count = 0;
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        if (board[(FIELD_SIZE - i - 1)][i] == player)
            ++streak_count;
        else
            streak_count = 0;

        if (streak_count == WIN_STREAK)
            return player;
    }

    return STATE_NEXT_STEP;
}

// Проход по главной диагонали
char Board::CheckDiagonal(char player) const
{
    int streak_count = 0;
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        if (board[i][i] == player)
            ++streak_count;
        else
            streak_count = 0;

        if (streak_count == WIN_STREAK)
            return player;
    }

    return STATE_NEXT_STEP;
}

// Проход по стобцам
char Board::CheckVertical(char player) const
{
    for (int y = 0; y < FIELD_SIZE; y++)
    {
        int streak_count = 0;
        for (int x = 0; x < FIELD_SIZE; x++)
        {
            if (board[y][x] == player)
                ++streak_count;
            else
                streak_count = 0;

            if (streak_count == WIN_STREAK)
                return player;
        }
    }

    return STATE_NEXT_STEP;
}

// Проход по строкам
char Board::CheckHorizontal(char player) const
{
    for (int y = 0; y < FIELD_SIZE; y++)
    {
        int streak_count = 0;
        for (int x = 0; x < FIELD_SIZE; x++)
        {
            if (board[x][y] == player)
                ++streak_count;
            else
                streak_count = 0;

            if (streak_count == WIN_STREAK)
                return player;
        }
    }

    return STATE_NEXT_STEP;
}
