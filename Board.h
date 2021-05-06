#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H

#include "Tile.h"
#include <vector> 
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;


class Board{
    public:
        Board();

        ~Board();


        void Board::addTile(Tile* tile, int row, int col);

        void Board::printBoard();

        void Board::resizeBoard(int row, int col);

        

        
    
    
    private:
        std::vector<std::vector<Tile*>> vecOfTiles;
        

    
};

#endif