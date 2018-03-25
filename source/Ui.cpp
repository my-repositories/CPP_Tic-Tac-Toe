#include "game_con.h"

Ui::Ui()
{
    m_game_state = true;
    m_player_step = 1;
    m_board = new Board();
}

Ui::~Ui()
{
    delete m_board;
}

// ����������� ��������� ����: �����/������/��������� ���
void Ui::Update()
{
    char* message;

    Display();
    switch (m_board->GameOver())
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
    
    RestartGame(message);
}

// ������������� ���� �������
void Ui::Move()
{
    GetStep(y, x);

    // ��� ������� ������
    // � ���� ��� ��������
    // �� ��� ���������� ������� ������
    // ����� ����� ����� ������� ������ �� ��� ���, ���� ��� �� ����� ���������
    if (m_player_step == 1)
    {
        if (m_board->SetCell(y - 1, x - 1, Board::CELL_X))
            m_player_step = 2;
    }
    else
    {
        if (m_board->SetCell(y - 1, x - 1, Board::CELL_O))
            m_player_step = 1;
    }
}
