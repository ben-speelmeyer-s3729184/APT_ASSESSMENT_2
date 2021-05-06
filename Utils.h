#ifndef ASSIGN2_UTILS_H
#define ASSIGN2_UTILS_H

#define QWIRKLE 6
#define MAX_TILES_LINE 6

#include "Board.h"
#include "Player.h"

class utils {
   public:
    utils();
    void updateScores(Player* player, Board* board, int row, int col, bool initialTurn);
    void adjacentTileChecker(bool& validMove, bool& colourMatch, bool& shapeMatch, Tile* tile1, Tile* tile2, Tile* toAddTile);

   private:
    int calculateLineScore(Board* board, int row, int rowIncrement, int col, int colIncrement);
};

#endif  //ASSIGN2_UTILS_H