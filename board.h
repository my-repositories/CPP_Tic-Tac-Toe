#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:
    enum { STATE_NEXT_STEP = -1, STATE_DRAW = 0, STATE_X_WINNER, STATE_O_WINNER};
    enum { CELL_EMPTY  = 0, CELL_X, CELL_O };

    explicit Board(const int field_size = 3, const int win_streak = 3);

    void ClearBoard() const;
    char GameOver() const;
    bool SetCell(int x, int y, char player) const;

    inline const char GetCell(int x, int y) const
    {
        return board[x][y];
    }
    inline const int GetSize() const
    {
        return FIELD_SIZE;
    }

private:
    const int FIELD_SIZE;
    const int WIN_STREAK;
    mutable std::vector< std::vector<char> > board;

    char CheckDraw() const;
    char CheckWin(const Board *board, char(Board::*pCheck)(char) const) const;

    char CheckAntiDiagonal(char player) const;
    char CheckDiagonal(char player) const;
    char CheckVertical(char player) const;
    char CheckHorizontal(char player) const;
};

#endif // !BOARD_H
