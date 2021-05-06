#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H

#include <string>
#include <vector>

#include "Tile.h"
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;

class Board {
   public:
    Board(){};

    ~Board();

    bool addTile(Tile* tile, int row, int col);

    Tile* getTile(int row, int col);

    void printBoard();

    void resizeBoard(int row, int col);

    void setGridToNullPtr();

    std::string boardToString();

    int asciiToInt(char letter);

    char intToAscii(int dec);

   private:
    std::vector<std::vector<Tile*>> vecOfTiles;
    int rows;
    int cols;
    std::string boardState;
};
#endif