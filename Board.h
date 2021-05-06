#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H

#include "Tile.h"
#include <vector> 
#include <string>
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;


class Board{
    public:
        Board(){};

        ~Board();


        bool addTile(Tile* tile, int row, int col);

        Tile* getTile(int row,int col);

        void printBoard();

        void resizeBoard(int row, int col);

        void setGridToNullPtr();

        string boardToString();

        
    
    
    private:
        std::vector<std::vector<Tile*>> vecOfTiles;
        int rows;
        int cols;
        

    
};

#endif