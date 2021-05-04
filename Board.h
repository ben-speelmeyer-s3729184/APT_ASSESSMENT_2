#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H
#include <vector> 





class Board{
    public:
        Board();
        ~Board();
        void populateBoard(Board board);
        string PrintBoard(Board board);
    
    private:
        #define EMPTY_SPACE "  "
        #define WALL "|"
        #define HEADER "__"
        std::vector<vector<string>> vec(55, vector<string>(55));
        

    
};

#endif