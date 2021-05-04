
#include "Board.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;


Board::Board(){
    this->vec = vec;
}    

Board::populateBoard(Board board){
    string Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int row = 55;
    int col = 55;
    int rowCount = 0;
    int alphaCount = 0;
    //add numbers to the top of the board
    for(int i = 0; i < row;i++){ 
        for(int j = 0; j < col; j++){
        if(i == 0 && j >= 1 && j % 2 == 0 && rowCount <=25){
                auto s = to_string(rowCount);
                [i][j] = s;
                rowCount++;
            }else{
                if(rowCount >= 11){
                    vec[i][j] = " ";
                }else{
                    vec[i][j] = "  ";
                }
                
            }
        }
    }
    //add line under the numbers of the board
    for(int i = 1; i < row;i++){
        for(int j = 0; j < col; j++){
            if(i == 1 && j >= 3 && j % 2 == 0){
                vec[i][j] = HEADER;
            }       
        }
    }
    //add grid lines
    for(int i = 2; i < row;i++){
        for(int j = 0; j < col; j++){
            if(i >=3 && i % 2 != 0 && j >= 2 && j % 2 == 0){
                vec[i][j] = WALL;
            }else{
                vec[i][j] = EMPTY_SPACE;
            }
        }
    }

    //add alpha reference
    for(int i = 0; i < row;i++){
        for(int j = 0; j < col; j++){
            if(j == 0 && i >= 3 && i % 2 != 0 ){
                if(alphaCount <= 25){
                    vec[i][j] = Alpha.at(alphaCount);
                    alphaCount++;
                }
            }
        }
    }
}
    
    
string Board::PrintBoard(Board board){
    for(int i = 0; i < 55;i++){
        for(int j = 0; j < 55;j++){
            cout << board[i][j];
        }

    }
}
   
   
   
