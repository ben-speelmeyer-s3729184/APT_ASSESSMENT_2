#include "Utils.h"

void Board::updateScores(Player player, Board board, int rows, int cols) {
    int currentScore = 1;
    int adjacentTiles = 0;
    bool adjacentTile = true;
    int currentCol = col - 1;
    while (adjacentTile) {
        if (board->getTile(row, currentCol) != nullptr) {
            --currentCol;
            ++adjacentTiles;
        } else {
            adjacentTile = false;
        }
    }
    //Checks right of chosen position.
    currentCol = col + 1;
    adjacentTile = true;
    while (adjacentTile) {
        if (board->getTile(row, currentCol) != nullptr) {
            ++currentCol;
            ++adjacentTiles;
        } else {
            adjacentTile = false;
        }
    }
    currentScore += adjacentTiles;
    if (adjacentTiles == 6) {
        currentScore += adjacentTiles;
    }
}