#ifndef GAME_QT_H
#define GAME_QT_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLabel>
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
    void Start() override;

private slots:
 void GetStep() override;
 void SetOptions() override;
 void ShowHelp();
 void RestartGame(char *message = 0) override;

private:
    int field_size, win_streak;
    QLabel *label_step;
    QLabel *stats;
    QLabel *label_wincounter_x;
    QLabel *label_wincounter_o;
    Ui::Game *ui;
    QVector< QVector<QPushButton*> > grid;

    void Display();
};

#endif // GAME_QT_H
