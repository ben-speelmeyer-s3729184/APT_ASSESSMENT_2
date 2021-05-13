// Copyright 2021
#include "ScoreManager.h"

ScoreManager::ScoreManager() {}

void ScoreManager::updateScores(Player* player, Board* board, int row, int col,
                                bool initialTilePlaced) {
  int currentScore = initialTilePlaced ? 0 : 1;
  currentScore += calculateLineScore(board, row, 1, col, 0);
  currentScore += calculateLineScore(board, row, 0, col, 1);
  player->addScore(currentScore);
}

int ScoreManager::calculateLineScore(Board* board, int row, int rowIncrement,
                                     int col, int colIncrement) {
  int score = 0;
  int otherTilesInLine = 0;
  bool adjacentTile = true;
  int currentRow = row - rowIncrement;
  int currentCol = col - colIncrement;

  while (adjacentTile) {
    if (currentRow < 0 || currentCol < 0) {
      adjacentTile = false;
    } else if (board->getTile(currentRow, currentCol) != nullptr) {
      currentRow -= rowIncrement;
      currentCol -= colIncrement;
      ++otherTilesInLine;
    } else {
      adjacentTile = false;
    }
  }
  // Checks right of chosen position.
  currentRow = row + rowIncrement;
  currentCol = col + colIncrement;
  adjacentTile = true;
  while (adjacentTile) {
    if (currentRow > board->getRows() || currentCol > board->getCols()) {
      adjacentTile = false;
    } else if (board->getTile(currentRow, currentCol) != nullptr) {
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
