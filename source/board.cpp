#include "../include/board.h"

// Create game field NxN
Board::Board(const int field_size, const int win_streak)
    :
    m_field_size(field_size),
    m_win_streak(win_streak),
    board(field_size, std::vector<CELL>(field_size))
{}

// Clear game field
void Board::ClearBoard()
{
    for (int y = 0; y < m_field_size; y++)
        for (int x = 0; x < m_field_size; x++)
            board[y][x] = CELL_EMPTY;
}

// Check game state ( DRAW | X_WIN | O_WIN | NEXT_STEP )
int Board::GameOver() const
{
    int state;

    // Array of check functions
    static int(Board::*checks[])(int) const =
    {
        &Board::CheckAntiDiagonal,
        &Board::CheckDiagonal,
        &Board::CheckVertical,
        &Board::CheckHorizontal
    };

    // Calling each check function
    for (int i = 0; i < 4; i++)
    {
        state = CheckWin(this, checks[i]);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    // check for tie
    state = CheckDraw();
    if (state == STATE_DRAW)
        return STATE_DRAW;

    return STATE_NEXT_STEP;
}

// Handle player step
bool Board::SetCell(int x, int y, CELL player)
{
    // validate coords
    if (x < 0 || y < 0 || x >= m_field_size || y >= m_field_size)
        return false;

    // check for empty cell
    if (board[x][y] == CELL_O || board[x][y] == CELL_X)
        return false;

    board[x][y] = player;
    return true;
}

// Set game field size
bool Board::SetFieldSize(int field_size)
{
    if (field_size < 2 || field_size > 20)
        return false;

    m_field_size = field_size;
    ResizeBoard();
    return true;
}

// Set win streak ( how much in a row )
bool Board::SetWinStreak(int win_streak)
{
    if (win_streak < 2 || win_streak > 20 || win_streak > m_field_size)
        return false;

    m_win_streak = win_streak;
    return true;
}

// Resize game board
void Board::ResizeBoard()
{
    board.resize(m_field_size);
    for (auto &it : board)
    {
        it.resize(m_field_size);
    }
}

// Check for tie!
int Board::CheckDraw() const
{
    // Find at least 1 empty cell
    for (int y = 0; y < m_field_size; y++)
    {
        for (int x = 0; x < m_field_size; x++)
        {
            if (board[y][x] == 0)
                return STATE_NEXT_STEP;
        }
    }

    return STATE_DRAW;
}

// Check for winner ( condition: 'int m_win_streak' in a row )
int Board::CheckWin(const Board *board, int(Board::*pCheck)(int) const) const
{
    int state;

    // Checkwin first player on the field (player = 1)
    // then Checkwin second player on the field (player = 2)
    for (int player = 1; player < 3; player++)
    {
        state = (board->*pCheck)(player);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    return STATE_NEXT_STEP;
}

// Check Secondary diagonals
int Board::CheckAntiDiagonal(int player) const
{
    int sz = m_field_size - 1;
    int df = m_field_size - m_win_streak + 1;

    for (int y = 0; y < df; y++)
    {
        for (int x = 0; x < df; x++)
        {
            int streak_count = 0;
            for (int i = 0; i < m_win_streak; i++)
            {
                if (board[sz - i - y][i + x] == player)
                    ++streak_count;
                else
                    streak_count = 0;

                if (streak_count == m_win_streak)
                    return player;
            }
        }
    }

    return STATE_NEXT_STEP;
}

// save backuyp
#if 0
// Check Secondary diagonal
int Board::CheckAntiDiagonal(int player) const
{
    int streak_count = 0;
    for (int i = 0; i < m_field_size; i++)
    {
        if (board[(m_field_size - i - 1)][i] == player)
            ++streak_count;
        else
            streak_count = 0;

        if (streak_count == m_win_streak)
            return player;
    }

    return STATE_NEXT_STEP;
}

// Check Main diagonal
int Board::CheckDiagonal(int player) const
{
    int streak_count = 0;
    for (int i = 0; i < m_field_size; i++)
    {
        if (board[i][i] == player)
            ++streak_count;
        else
            streak_count = 0;

        if (streak_count == m_win_streak)
            return player;
    }

    return STATE_NEXT_STEP;
}
#endif

// Check Main diagonals
int Board::CheckDiagonal(int player) const
{
    int df = m_field_size - m_win_streak + 1;

    for (int y = 0; y < df; y++)
    {
        for (int x = 0; x < df; x++)
        {
            int streak_count = 0;
            for (int i = 0; i < m_win_streak; i++)
            {
                if (board[i + y][i + x] == player)
                    ++streak_count;
                else
                    streak_count = 0;

                if (streak_count == m_win_streak)
                    return player;
            }
        }
    }

    return STATE_NEXT_STEP;
}

// Check columns
int Board::CheckVertical(int player) const
{
    for (int y = 0; y < m_field_size; y++)
    {
        int streak_count = 0;
        for (int x = 0; x < m_field_size; x++)
        {
            if (board[y][x] == player)
                ++streak_count;
            else
                streak_count = 0;

            if (streak_count == m_win_streak)
                return player;
        }
    }

    return STATE_NEXT_STEP;
}

// Check rows
int Board::CheckHorizontal(int player) const
{
    for (int y = 0; y < m_field_size; y++)
    {
        int streak_count = 0;
        for (int x = 0; x < m_field_size; x++)
        {
            if (board[x][y] == player)
                ++streak_count;
            else
                streak_count = 0;

            if (streak_count == m_win_streak)
                return player;
        }
    }

    return STATE_NEXT_STEP;
}
