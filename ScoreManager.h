// Copyright 2021
#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#define QWIRKLE 6
#define MAX_TILES_LINE 6

#include "Board.h"
#include "Player.h"

class ScoreManager {
 public:
  ScoreManager();
  void updateScores(Player* player, Board* board, int row, int col,
                    bool initialTurn);

 private:
  int calculateLineScore(Board* board, int row, int rowIncrement, int col,
                         int colIncrement);
};

#endif  // SCOREMANAGER_H_
