
#include "Board.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;




bool Board::addTile(Tile* tile,int row, int col){
    vecOfTiles[row][col] = tile;
    if(vecOfTiles[row][col] == tile){
        return true;
    }else{
        return false;
    }
}

void Board::printBoard(){
    string Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphaCount = 0;
    cout << "  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25   " << endl;
    cout << "  -----------------------------------------------------------------------------" << endl;
   
    for(int i = 0; i < rows;i++){
        if(alphaCount < 26){
            cout << Alpha.at(alphaCount);
            alphaCount++;
        }
        cout << WALL;
        for(int j = 0; j < cols;j++){
            if(vecOfTiles[i][j] == nullptr){
                cout << "  " << WALL;
            }else{
                cout << vecOfTiles[i][j]->toString() << WALL;
            }
        }
        cout << endl;  
    }
}

void Board::resizeBoard(int row, int col){
    vecOfTiles.resize(row);
    for(int i = 0; i < row;i++){
        vecOfTiles[i].resize(col);
    }
    rows = row;
    cols = col;
}

Tile* Board::getTile(int row,int col){
    return vecOfTiles[row][col];
}


    
    

   
   
   
