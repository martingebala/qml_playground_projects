#include "game.h"

bool Game::clickedField(QModelIndex index)
{

    int current_symbol = (m_current_player == 0) ? Marks::Nought : Marks::Cross;
    game_board_model.setData(index, current_symbol, GameBoardModel::MarkRole);

    if(game_board_model.player_wins(index, m_marks_to_win, current_symbol))
    {
        if(current_symbol == Marks::Nought)
        {
            qDebug() << "Noughts wins!";
            emit noughtsWins();
        }
        else if(current_symbol == Marks::Cross)
        {
            qDebug() << "Crosses wins!";
            emit crossesWins();
        }
    }

    m_current_player = (++m_current_player) % m_number_of_players;


    return true;
}

void Game::resetGame(){
    game_board_model.createBoard(32,24);
}

Game::Game():
    m_number_of_players(2),
    m_marks_to_win(5)
{
    game_board_model.createBoard(32,24);
}

