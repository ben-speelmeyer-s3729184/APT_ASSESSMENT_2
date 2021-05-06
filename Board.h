#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H

#include <vector>

#include "Tile.h"
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;

class Board {
   public:
    Board();

    ~Board();

    void addTile(Tile* tile, int row, int col);

    void printBoard();

    void resizeBoard(int row, int col);

    Tile* getTile(int row, int col);

   private:
    std::vector<std::vector<Tile*>> vecOfTiles;
};

#endif