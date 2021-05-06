#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H
<<<<<<< HEAD

#include "Tile.h"
#include <vector> 
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;
=======
#include <vector> 



>>>>>>> Board commit


class Board{
    public:
        Board();
<<<<<<< HEAD

        ~Board();


        void Board::addTile(Tile* tile, int row, int col);

        void Board::printBoard();

        void Board::resizeBoard(int row, int col);

        

        
    
    
    private:
        std::vector<std::vector<Tile*>> vecOfTiles;
=======
        ~Board();
        void populateBoard(Board board);
        string PrintBoard(Board board);
    
    private:
        #define EMPTY_SPACE "  "
        #define WALL "|"
        #define HEADER "__"
        std::vector<vector<string>> vec(55, vector<string>(55));
>>>>>>> Board commit
        

    
};

#endif