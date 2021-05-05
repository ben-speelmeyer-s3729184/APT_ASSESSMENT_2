
#include "Board.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;


Board::Board(){} 

void Board::addTile(Tile tile,int row, int col){
    vecOfTiles[row][col] = tile;
}

void Board::initilizeBoard(){
    
}



    
    
void Board::displayBoard(){
    for(int i = 0; i < 25;i++){
        for(int j = 0; j < 25;j++){
            cout << vecOfTiles[i][j];
        }

    }
}
   
   
   
