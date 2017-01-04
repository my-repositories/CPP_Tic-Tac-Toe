#include "../include/settings.h"

#if MY_GAME == QT_GAME

#include "../include/game_qt.h"
#include "ui_game_qt.h"
#include <QInputDialog>
#include <QMessageBox>

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    BaseGame(),
    field_size(3), win_streak(3),
    ui(new Ui::Game),
    grid(3, QVector<QPushButton*>(3))
{
    ui->setupUi(this);
    ui->menuBar->addAction(tr("Restart"), this, SLOT(RestartGame()));
    ui->menuBar->addAction(tr("Help"), this, SLOT(ShowHelp()));
    ui->menuBar->addAction(tr("Quit"), this, SLOT(close()));
    label_step = new QLabel(this);
    stats = new QLabel(this);
    label_wincounter_x = new QLabel(this);
    label_wincounter_o = new QLabel(this);
    SetOptions();
}

Game::~Game()
{
    delete label_step;
    delete stats;
    delete label_wincounter_o;
    delete label_wincounter_x;
    delete ui;
}

// Ask Game Settings (Field size & Win streak)
void Game::SetOptions()
{
    field_size = QInputDialog::getInt(0, tr("Settings"),
                                     tr("Field size:"), 3, 2, 20, 1, 0);
    win_streak = QInputDialog::getInt(0, tr("Settings"),
                                     tr("Win Streak:"), 3, 2, field_size, 1, 0);

    m_board->SetFieldSize(field_size);
    m_board->SetWinStreak(win_streak);
}

// Create buttons grid
void Game::Start()
{
    int size = 50 + 30 * field_size;
    this->setFixedSize(100 + size, 100 + size);

    label_step->setText("Player Step:\n        X");
    label_step->setGeometry(QRect(QPoint(size, 15), QSize(150, 100)));
    label_step->show();

    stats->setText("Game Stats:");
    stats->setGeometry(QRect(QPoint(10 + size / 2, size), QSize(150, 50)));
    stats->show();

    label_wincounter_x->setText("X Wins count: " + QString::number(m_count_win_x));
    label_wincounter_x->setGeometry(QRect(QPoint(size / 2, size + 20), QSize(150, 50)));
    label_wincounter_x->show();

    label_wincounter_o->setText("O Wins count: " + QString::number(m_count_win_o));
    label_wincounter_o->setGeometry(QRect(QPoint(size / 2, size + 35), QSize(150, 50)));
    label_wincounter_o->show();

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
            btn->setGeometry(QRect(QPoint(10+ m_x*30, 40 + m_y*30), QSize(30, 30)));
            btn->show();
            connect(btn, SIGNAL (released()), this, SLOT (GetStep()));
        }
    }
    show();
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
    label_wincounter_x->setText("X Wins count: " + QString::number(m_count_win_x));
    label_wincounter_o->setText("O Wins count: " + QString::number(m_count_win_o));
    QMessageBox::StandardButton reply = QMessageBox::question
    (
        this,
        QString::QString(message),
        "Restart Game?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes)
    {
        m_game_state = true;
        label_step->setText("Player Step:\n        X");
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
    QPalette pallete;

    switch (m_board->GetCell(m_y, m_x))
    {
    case Board::CELL_X:
        ch = 'X';
        pallete.setColor(QPalette::ButtonText,Qt::blue);
        break;

    case Board::CELL_O:
        ch = 'O';
        pallete.setColor(QPalette::ButtonText,Qt::red);
        break;

    default: break;
    }

    if(m_player_step == 1)
        label_step->setText("Player Step:\n        X");
    else
        label_step->setText("Player Step:\n        O");

    grid[m_y][m_x]->setText(ch);
    grid[m_y][m_x]->setPalette(pallete);
}

void Game::ShowHelp()
{
    QMessageBox msg;
    msg.setText("The player who succeeds in placing three(or more) of their marks in a horizontal, vertical, or diagonal row wins the game.");
    msg.exec();
}

#endif
