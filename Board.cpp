// Copyright 2021

#include <iostream>
#include <string>
#include <vector>

#include "Tile.h"
#include "Board.h"



Board::Board() {}
Board::~Board() {
    vecOfTiles.clear();
}

void Board::addTile(Tile* tile, int row, int col) {
    vecOfTiles[row][col] = tile;
}

void Board::printBoard() {
    std::string Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphaCount = 0;
    std::cout << "    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 " << std::endl;
    std::cout << "    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std::endl;

    for (unsigned int i = 0; i < vecOfTiles.size(); i++) {
        std::cout << Alpha.at(alphaCount);
        alphaCount++;
        std::cout << WALL;
        for (unsigned int j = 0; j < vecOfTiles[i].size(); i++) {
            if (vecOfTiles[i][j] == nullptr) {
                std::cout << "  |";
            } else {
                std::cout << vecOfTiles[i][j]->toString() + "|";
            }
            std::cout << std::endl;
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
