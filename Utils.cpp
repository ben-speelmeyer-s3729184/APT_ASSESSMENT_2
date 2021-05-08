#include "utils.h"

#include <iostream>

utils::utils(){};

void utils::updateScores(Player* player, Board* board, int row, int col,
                         bool initialTilePlaced) {
  int currentScore = initialTilePlaced ? 0 : 1;
  currentScore += calculateLineScore(board, row, 1, col, 0);
  currentScore += calculateLineScore(board, row, 0, col, 1);
  player->addScore(currentScore);
}

int utils::calculateLineScore(Board* board, int row, int rowIncrement, int col,
                              int colIncrement) {
  int score = 0;
  int otherTilesInLine = 0;
  bool adjacentTile = true;
  int currentRow = row - rowIncrement;
  int currentCol = col - colIncrement;
  while (adjacentTile) {
    if (board->getTile(currentRow, currentCol) != nullptr) {
      currentRow -= rowIncrement;
      currentCol -= colIncrement;
      ++otherTilesInLine;
    } else {
      adjacentTile = false;
    }
  }
  // Checks right of chosen position.
  currentRow = row + 1;
  adjacentTile = true;
  while (adjacentTile) {
    if (board->getTile(currentRow, currentCol) != nullptr) {
      currentRow += rowIncrement;
      currentCol += colIncrement;
      ++otherTilesInLine;
    } else {
      adjacentTile = false;
    }
  }
  if (otherTilesInLine > 0) {
    score += otherTilesInLine + 1;
  }
  if (otherTilesInLine + 1 == MAX_TILES_LINE) {
    score += QWIRKLE;
  }
  return score;
}

void utils::adjacentTileChecker(bool& validMove, bool& colourMatch,
                                bool& shapeMatch, Tile* tile1, Tile* tile2,
                                Tile* toAddTile) {
  if (tile1 == nullptr && tile2 == nullptr) {
    validMove = true;
  } else if (tile1 == nullptr) {
    if (toAddTile->colour == tile2->colour) {
      validMove = true;
      colourMatch = true;
    } else if (toAddTile->shape == tile2->shape) {
      validMove = true;
      shapeMatch = true;
    }
  } else if (tile2 == nullptr) {
    if (toAddTile->colour == tile1->colour) {
      validMove = true;
      colourMatch = true;
    } else if (toAddTile->shape == tile1->shape) {
      validMove = true;
      shapeMatch = true;
    }
  } else {
    if ((tile1->colour == toAddTile->colour &&
         tile2->colour == toAddTile->colour)) {
      validMove = true;
      colourMatch = true;
    } else if (tile1->shape == toAddTile->shape &&
               tile2->shape == toAddTile->shape) {
      validMove = true;
      shapeMatch = true;
    }
  }
}