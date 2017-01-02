#ifndef GAME_QT_H
#define GAME_QT_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>

namespace Ui {
class Game;
}

class Game : public QMainWindow
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

    // [delete]
    int y,x;
    // [/delete]

    // [override other virtual method are:]
    void SetOptions();
    void RestartGame(char *message);
    // [/override]
};

#endif // GAME_QT_H
