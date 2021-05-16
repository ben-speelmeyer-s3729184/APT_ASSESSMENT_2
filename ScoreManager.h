// Copyright 2021
#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include "Board.h"
#include "Player.h"
#include "Definitions.h"

class ScoreManager {
public:

    /*
    * Constructor
    */
    ScoreManager();

    /*
    * Calculates the score to add to a player
    */
    void updateScores(Player* player, Board* board, int row, int col,
                                    bool initialTurn);

private:

    /*
    * Calculates the score of a line
    */
    int calculateLineScore(Board* board, int row, int rowIncrement, int col,
                                                int colIncrement);

};

#endif    // SCOREMANAGER_H_
