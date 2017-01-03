#ifndef GAME_QT_H
#define GAME_QT_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include "../include/base_game.h"

namespace Ui {
class Game;
}

class Game
        : public QMainWindow,
          public BaseGame

{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    void Start();

private slots:
 void GetStep();

private:
    int field_size, win_streak;
    Ui::Game *ui;
    QVector< QVector<QPushButton*> > grid;

    void SetOptions();
    void RestartGame(char *message);
    void Display();
};

#endif // GAME_QT_H
