#include "game_qt.h"
#include "ui_game_qt.h"
#include <QInputDialog>
#include <QMessageBox>

Game::Game(QWidget *parent) :
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

// Задание настроек игры
void Game::SetOptions()
{
    field_size = QInputDialog::getInt(this, tr("Settings"),
                                     tr("Field size:"), 3, 2, 20, 1, nullptr);
    win_streak = QInputDialog::getInt(this, tr("Settings"),
                                     tr("Win Streak:"), 3, 2, 20, 1, nullptr);
    ui->label->setText(QString::number(field_size));

    //m_board->SetFieldSize(field_size);
    //m_board->SetWinStreak(win_streak);
}

void Game::Start()
{
    show();

    //grid = QVector< QVector<QPushButton*> >(field_size);
    grid.resize(field_size);
    for(int i = 0; i < field_size; i++)
    {
        //grid[i] = QVector<QPushButton*>(field_size);
        grid[i].resize(field_size);
        for(int j = 0; j < field_size; j++)
        {
            QPushButton *btn = new QPushButton(QString::number( i*field_size + j ), this);
            grid[i][j] = btn;
            btn->setGeometry(QRect(QPoint(10+ j*30, 10 + i*30), QSize(30, 30)));
            btn->show();
            connect(btn, SIGNAL (clicked()), this, SLOT (GetStep()));
        }
    }

    /*while (m_game_state)
    {
        Display();
        GetStep();
        Move();
        Update();
    }*/
}

// Обработка хода игрока
void Game::GetStep()
{
    QPushButton* button = (QPushButton*)QObject::sender();

    for(y = 0; y < field_size; y++)
    {
        for(x = 0; x < field_size; x++)
        {
            if(button == grid[y][x])
            {
                button->setText("X");
                break;
            }
        }
    }

    int t = field_size * field_size;
    for(y = 0; y < field_size; y++)
    {
        for(x = 0; x < field_size; x++)
        {
            if(grid[y][x]->text() == "X")
            {
                --t;
            }
        }
    }
    if (t == 0 )
    {
        QMessageBox msgBox;
        msgBox.setText("победа");
        msgBox.exec();
        return;
    }
}

// Продолжить игру сначала или выйти
void Game::RestartGame(char *message)
{
    /*std::cout << message << " Желаете сыграть еще раз? 1/0: ";
    std::cin.ignore();
    if (std::getchar() == '0')
        m_game_state = false;
    else
    {
        m_player_step = 1;
        m_board->ClearBoard();
    }*/
}
