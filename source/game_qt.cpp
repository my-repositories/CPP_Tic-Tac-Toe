#include "../include/settings.h"

#if MY_GAME == QT_GAME

#include "../include/game_qt.h"
#include "ui_game_qt.h"
#include <QInputDialog>
#include <QMessageBox>

Game::Game(QWidget *parent) :
    BaseGame(),
    QMainWindow(parent),
    ui(new Ui::Game),
    grid(3, QVector<QPushButton*>(3)),
    field_size(3), win_streak(3)
{
    ui->setupUi(this);
    SetOptions();
}

Game::~Game()
{
    delete ui;
}

// Ask Game Settings (Field size & Win streak)
void Game::SetOptions()
{
    field_size = QInputDialog::getInt(this, tr("Settings"),
                                     tr("Field size:"), 3, 2, 20, 1, nullptr);
    win_streak = QInputDialog::getInt(this, tr("Settings"),
                                     tr("Win Streak:"), 3, 2, 20, 1, nullptr);

    m_board->SetFieldSize(field_size);
    m_board->SetWinStreak(win_streak);
}

// Create buttons grid
void Game::Start()
{
    show();

    //grid = QVector< QVector<QPushButton*> >(field_size);
    grid.resize(field_size);
    for(m_y = 0; m_y < field_size; m_y++)
    {
        //grid[m_y] = QVector<QPushButton*>(field_size);
        grid[m_y].resize(field_size);
        for(m_x = 0; m_x < field_size; m_x++)
        {
            QPushButton *btn = new QPushButton(" ", this);
            grid[m_y][m_x] = btn;
            btn->setGeometry(QRect(QPoint(10+ m_x*30, 10 + m_y*30), QSize(30, 30)));
            btn->show();
            connect(btn, SIGNAL (released()), this, SLOT (GetStep()));
        }
    }
}

// Handle player step ( signal: released button )
void Game::GetStep()
{
    QPushButton* button = (QPushButton*)QObject::sender();

    for(m_y = 0; m_y < field_size; m_y++)
    {
        for(m_x = 0; m_x < field_size; m_x++)
        {
            if(button == grid[m_y][m_x])
            {
                Move();
                Display();
                Update();
                return;
            }
        }
    }
}

// Ask for Restart or Quit
void Game::RestartGame(char *message)
{
    QMessageBox::StandardButton reply = QMessageBox::question
    (
        this,
        QString::QString(message),
        "Play again?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::No)
    {
        m_game_state = false;
        QApplication::quit();
    }
    else
    {
        m_player_step = 1;
        m_board->ClearBoard();

        for(m_y = 0; m_y < field_size; m_y++)
            for(m_x = 0; m_x < field_size; m_x++)
                grid[m_y][m_x]->setText(" ");
    }
}

// Change button text
void Game::Display()
{
    QChar ch = ' ';

    switch (m_board->GetCell(m_y, m_x))
    {
    case Board::CELL_X: ch = 'X'; break;
    case Board::CELL_O: ch = 'O'; break;
    default: break;
    }

    grid[m_y][m_x]->setText(ch);
}

#endif
