#include "Board.h"

#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"

using namespace std;

Board::Board(){

};

Board::~Board() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (boardVecs[i][j] != nullptr) {
        Tile* tileToDelete = boardVecs[i][j];
        boardVecs[i][j] = nullptr;
        delete tileToDelete;
      }
    }
  }
  boardVecs.clear();
}

bool Board::addTile(Tile* tile, int row, int col) {
  boardVecs[row][col] = tile;
  if (boardVecs[row][col] == tile) {
    return true;
  } else {
    return false;
  }
}

std::string Board::printBoard() {
  std::string boardAppearance;
  string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int alphaCount = 0;
  boardAppearance.append(EMPTY_SPACE " ");
  boardAppearance.append(
      "0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 "
      "23 24 25\n");
  boardAppearance.append(EMPTY_SPACE " ");
  boardAppearance.append(
      "------------------------------------------------------------------------"
      "-----\n");

  for (int i = 0; i < rows; i++) {
    if (alphaCount < 26) {
      boardAppearance.push_back(alpha[i]);
      boardAppearance.push_back(' ');
      boardAppearance.append(WALL);
    }
    for (int j = 0; j < cols; j++) {
      if (boardVecs[i][j] == nullptr) {
        boardAppearance.append("  " WALL);
      } else {
        boardAppearance.append(boardVecs[i][j]->toString() + WALL);
      }
    }
    boardAppearance.append("\n");
  }
  return boardAppearance;
}

void Board::resizeBoard(int row, int col) {
  boardVecs.resize(row);
  for (int i = 0; i < row; i++) {
    boardVecs[i].resize(col);
  }
  rows = row;
  cols = col;
}

Tile* Board::getTile(int row, int col) { return boardVecs[row][col]; }
int Board::getRows() { return rows; }
int Board::getCols() { return cols; }

string Board::boardToString() {
  std::string boardState = "";
  boardState.append(std::to_string(rows) + "," + std::to_string(cols));
  boardState.append("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (boardVecs[i][j] != nullptr) {
        boardState.append(boardVecs[i][j]->toString());
        boardState.append("@");
        boardState.push_back(intToAscii(i));
        string str = to_string(j);
        boardState.append(str);
        boardState.append(", ");
      }
    }
  }
  boardState.pop_back();
  boardState.pop_back();
  boardState.append("\n");
  return boardState;
}

int Board::asciiToInt(char letter) {
  int i = int(letter);
  i = i - 65;
  return i;
}

char Board::intToAscii(int dec) {
  dec = dec + 65;
  char letter = dec;
  return letter;
}

// Check tile placement
bool Board::checkTilePlacement(Tile* tile, int row, int col,
                               bool initialTilePlaced) {
  bool tilePlaceable = false;
  if (boardVecs[row][col] == nullptr) {
    bool adjacentTiles = checkForAdjacency(row, col);
    if (initialTilePlaced && adjacentTiles) {
      bool leftRightCheck = checkAdjacentTiles(row, 0, col, 1, tile);
      bool upDownCheck = checkAdjacentTiles(row, 1, col, 0, tile);

      if (leftRightCheck && upDownCheck) {
        tilePlaceable = true;
      }
    } else if (!initialTilePlaced) {
      tilePlaceable = true;
    }
  }
  return tilePlaceable;
}

// Checks tiles adjacent to tile placement location for valid move
bool Board::checkAdjacentTiles(int row, int rowAdjustment, int col,
                               int colAdjustment, Tile* tile) {
  bool validMove = false;
  Tile* prevTile = nullptr;
  Tile* postTile = nullptr;
  if (row - rowAdjustment >= 0 && col - colAdjustment >= 0) {
    prevTile = boardVecs[row - rowAdjustment][col - colAdjustment];
  }
  if (row + rowAdjustment < rows && col + colAdjustment < cols) {
    postTile = boardVecs[row + rowAdjustment][col + colAdjustment];
  }
  bool colourMatch = false;
  bool shapeMatch = false;

  // check whether tile to be added can be placed between
  // the positions either above and below or left and right
  // of the chosen position.
  utils utilities;
  utilities.adjacentTileChecker(validMove, colourMatch, shapeMatch, prevTile,
                                postTile, tile);

  // Checking if line the tile is to be added to is valid
  // same colour, or same shape, and no identical tile
  if (validMove) {
    // To left or above first, then right or down second.
    int adjacentTiles = 0;
    int adjacentTilesB = lineChecker(row, col, -rowAdjustment, -colAdjustment,
                                     shapeMatch, colourMatch, tile);
    int adjacentTilesA = lineChecker(row, col, rowAdjustment, colAdjustment,
                                     shapeMatch, colourMatch, tile);
    if (adjacentTilesB == -1 || adjacentTilesA == -1) {
      validMove = false;
    } else {
      adjacentTiles = adjacentTilesB + adjacentTilesA;
    }
    // Final check. If number of adjacent tiles in this column is more than 5
    // then tile cannot be placed.
    if (adjacentTiles > 5) {
      validMove = false;
    }
  }
  return validMove;
}

int Board::lineChecker(int row, int col, int rowAdjustment, int colAdjustment,
                       bool shapeMatch, bool colourMatch, Tile* tile) {
  int adjacentTiles = 0;
  bool validMove = true;
  int currentRow = row + rowAdjustment;
  int currentCol = col + colAdjustment;
  bool adjacentTile = true;
  while (adjacentTile && validMove) {
    Tile* tileCheck;
    if (currentRow > rows || currentCol > cols || currentCol < 0 ||
        currentRow < 0) {
      tileCheck = nullptr;
    } else {
      tileCheck = boardVecs[currentRow][currentCol];
    }

    if (tileCheck != nullptr) {
      if (colourMatch && tile->colour != tileCheck->colour) {
        validMove = false;
      } else if (shapeMatch && tile->shape != tileCheck->shape) {
        validMove = false;
      } else if (tileCheck->shape == tile->shape &&
                 tileCheck->colour == tile->colour) {
        validMove = false;
      }
      currentCol += colAdjustment;
      currentRow += rowAdjustment;
      ++adjacentTiles;
    } else {
      adjacentTile = false;
    }
    if (!validMove) {
      adjacentTiles = -1;
    }
  }
  return adjacentTiles;
}

// Checked whether a tile is being placed next to another tile.
bool Board::checkForAdjacency(int row, int col) {
  bool tileAdjacent = false;
  // Add bounds checking.
  if (row - 1 >= 0) {
    if (boardVecs[row - 1][col] != nullptr) {
      tileAdjacent = true;
    }
  }
  if (col - 1 >= 0) {
    if (boardVecs[row][col - 1] != nullptr) {
      tileAdjacent = true;
    }
  }
  if (row + 1 < rows) {
    if (boardVecs[row + 1][col] != nullptr) {
      tileAdjacent = true;
    }
  }
  if (col + 1 < cols) {
    if (boardVecs[row][col + 1] != nullptr) {
      tileAdjacent = true;
    }
  }
  return tileAdjacent;
}