#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QDebug>
#include "game_board_model.h"


class Game : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE bool clickedField(QModelIndex index);
    Q_INVOKABLE void resetGame();
    Game();

    GameBoardModel game_board_model;

private:

    int m_current_player;
    int m_number_of_players;
    int m_marks_to_win;

signals:
    void crossesWins();
    void noughtsWins();
};

#endif // GAME_H
