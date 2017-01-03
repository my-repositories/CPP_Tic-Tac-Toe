#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:
    enum STATE { STATE_NEXT_STEP = -1, STATE_DRAW = 0, STATE_X_WINNER, STATE_O_WINNER};
    enum CELL { CELL_EMPTY  = 0, CELL_X, CELL_O };

    explicit Board(const int field_size = 3, const int win_streak = 3);

    void ClearBoard();
    int GameOver() const;
    bool SetCell(int x, int y, CELL player);
    bool SetFieldSize(int field_size = 3);
    bool SetWinStreak(int win_streak = 3);
    void ResizeBoard();

    inline CELL GetCell(int y, int x) const
    {
        return board[y][x];
    }
    inline int GetSize() const
    {
        return m_field_size;
    }
    inline int GetWinStreak() const
    {
        return m_win_streak;
    }

private:
    int m_field_size;
    int m_win_streak;
    std::vector< std::vector<CELL> > board;

    int CheckDraw() const;
    int CheckWin(const Board *board, int(Board::*pCheck)(int) const) const;

    int CheckAntiDiagonal(int player) const;
    int CheckDiagonal(int player) const;
    int CheckVertical(int player) const;
    int CheckHorizontal(int player) const;
};

#endif // !BOARD_H
