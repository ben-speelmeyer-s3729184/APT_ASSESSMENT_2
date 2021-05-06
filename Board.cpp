
#include "Board.h"

#include <iostream>
#include <string>
#include <vector>

#include "Tile.h"

using namespace std;

Board::Board() {}
Board::~Board() {
    vecOfTiles.clear();
}

void Board::addTile(Tile* tile, int row, int col) {
    vecOfTiles[row][col] = tile;
}

void Board::printBoard() {
    string Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphaCount = 0;
    cout << "    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 " << endl;
    cout << "    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl;

    for (unsigned int i = 0; i < vecOfTiles.size(); i++) {
        cout << Alpha.at(alphaCount);
        alphaCount++;
        cout << WALL;
        for (unsigned int j = 0; j < vecOfTiles[i].size(); i++) {
            if (vecOfTiles[i][j] == nullptr) {
                cout << "  |";
            } else {
                cout << vecOfTiles[i][j]->toString() + "|";
            }
            cout << endl;
        }
    }
}

void Board::resizeBoard(int row, int col) {
    vecOfTiles.resize(row);
    for (int i = 0; i < row; i++) {
        vecOfTiles[row].resize(col);
    }
}

Tile* Board::getTile(int row, int col) {
    return nullptr;
}
