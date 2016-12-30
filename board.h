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

    inline CELL GetCell(int x, int y) const
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
    std::vector< std::vector<CELL> > board;

    int CheckDraw() const;
    int CheckWin(const Board *board, int(Board::*pCheck)(int) const) const;

    int CheckAntiDiagonal(int player) const;
    int CheckDiagonal(int player) const;
    int CheckVertical(int player) const;
    int CheckHorizontal(int player) const;
};

#endif // !BOARD_H
