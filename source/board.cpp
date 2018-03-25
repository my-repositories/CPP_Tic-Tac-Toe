#include "board.h"

// �������� �������� ���� NxN
Board::Board(const int field_size, const int win_streak)
    :
    m_field_size(field_size),
    m_win_streak(win_streak),
    board(field_size, std::vector<CELL>(field_size))
{}

// �������� ������� ����
void Board::ClearBoard()
{
    for (int y = 0; y < m_field_size; y++)
        for (int x = 0; x < m_field_size; x++)
            board[y][x] = CELL_EMPTY;
}

// ����������� ����� ����
int Board::GameOver() const
{
    int state;

    // �������� �� �����
    state = CheckDraw();
    if (state == STATE_DRAW)
        return STATE_DRAW;

    // ������ ������� � ���������� �� ������
    static int(Board::*checks[])(int) const =
    {
        &Board::CheckAntiDiagonal,
        &Board::CheckDiagonal,
        &Board::CheckVertical,
        &Board::CheckHorizontal
    };

    // ������ �� ������� �������
    for (int i = 0; i < 4; i++)
    {
        state = CheckWin(this, checks[i]);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    return STATE_NEXT_STEP;
}

// ��������� ���� ������
bool Board::SetCell(int x, int y, CELL player)
{
    // ��������� ���������
    if (x < 0 || y < 0 || x >= m_field_size || y >= m_field_size)
        return false;

    // ���� ������ ������
    if (board[x][y] == CELL_O || board[x][y] == CELL_X)
        return false;

    board[x][y] = player;
    return true;
}

// ��������� ������� �������� ����
bool Board::SetFieldSize(int field_size)
{
    // ��������� ���������
    if (field_size < 2 || field_size > 20)
        return false;

    m_field_size = field_size;
    ResizeBoard();
    return true;
}

// ������� ���������� ���������� (������� ������ � ���)
bool Board::SetWinStreak(int win_streak)
{
    // ��������� ���������
    if (win_streak < 2 || win_streak > 20)
        return false;

    m_win_streak = win_streak;
    return true;
}

// ��������� �������� �������� ����
void Board::ResizeBoard()
{
    board.resize(m_field_size);
    for (auto &it : board)
    {
        it.resize(m_field_size);
    }
}

// ����������� ������
int Board::CheckDraw() const
{
    // ���� ���� �� 1 ������ ������
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

// ����������� ����������
int Board::CheckWin(const Board *board, int(Board::*pCheck)(int) const) const
{
    int state;

    // ������ �� ���� ������ ������� (player = 1)
    // ����� ������ ������� (player = 2)
    for (int player = 1; player < 3; player++)
    {
        state = (board->*pCheck)(player);
        if (state == STATE_X_WINNER || state == STATE_O_WINNER)
            return state;
    }

    return STATE_NEXT_STEP;
}

// ������ �� �������� ���������
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

// ������ �� ������� ���������
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

// ������ �� �������
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

// ������ �� �������
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
