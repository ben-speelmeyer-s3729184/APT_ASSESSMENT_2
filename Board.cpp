// Copyright 2021
#include "Board.h"

#include <iostream>

Board::Board() {
    rows = 0;
    cols = 0;
}

Board::Board(Board& other) {
    // for (auto tilevec : other.boardVecs) {
    //     boardVecs.push_back()
    //     for (auto tile : tilevec) {
    //     }
    // }
    resizeBoard(other.rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (other.boardVecs[i][j] != nullptr) {
                boardVecs[i][j] = new Tile(*other.boardVecs[i][j]);
            }
        }
    }
    rows = other.rows;
    cols = other.cols;
}

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
    bool tileAdded = false;
    if (boardVecs[row][col] == nullptr) {
        boardVecs[row][col] = tile;
        tileAdded = true;
    }
    return tileAdded;
}

std::string Board::printBoard() {
    std::string boardAppearance;
    std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphaCount = 0;
    boardAppearance.append(EMPTY_SPACE " ");
    for (int i = 0; i < cols; ++i) {
        std::string toAppend = i < 10 ?
                              std::to_string(i) + EMPTY_SPACE :
                              std::to_string(i) + " ";
        boardAppearance.append(toAppend);
    }
    boardAppearance.append("\n");
    boardAppearance.append(EMPTY_SPACE);
    for (int i = 0; i < cols * 3; ++i) {
        boardAppearance.append("-");
    }
    boardAppearance.append("-\n");

    for (int i = 0; i < rows; i++) {
        if (alphaCount < 26) {
            boardAppearance.push_back(alpha[i]);
            boardAppearance.push_back(' ');
            boardAppearance.append(WALL);
        }
        for (int j = 0; j < cols; j++) {
            if (boardVecs[i][j] == nullptr) {
                boardAppearance.append("    " WALL);
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

std::string Board::boardToString() {
    std::string boardState = "";
    bool initialTileAdded = false;
    boardState.append(std::to_string(rows) + "," + std::to_string(cols));
    boardState.append("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (boardVecs[i][j] != nullptr) {
                if (initialTileAdded) {
                    boardState.append(", " + boardVecs[i][j]->toString() + "@");
                } else {
                    boardState.append(boardVecs[i][j]->toString() + "@");
                    initialTileAdded = true;
                }
                boardState.push_back(intToAscii(i));
                std::string str = std::to_string(j);
                boardState.append(str);
            }
        }
    }
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
                               int colAdjustment, Tile* tileToAdd) {
    bool validMove = false;
    Tile* prevTile = nullptr;
    Tile* postTile = nullptr;
    if (row - rowAdjustment >= 0 && col - colAdjustment >= 0) {
        prevTile = boardVecs[row - rowAdjustment][col - colAdjustment];
    }
    if (row + rowAdjustment < rows && col + colAdjustment < cols) {
        postTile = boardVecs[row + rowAdjustment][col + colAdjustment];
    }
    // check whether tile to be added can be placed between
    // the positions either above and below or left and right
    // of the chosen position.
    bool colourMatch = false;
    bool shapeMatch = false;
    if (prevTile == nullptr && postTile == nullptr) {
        validMove = true;
    } else if (prevTile == nullptr) {
        if (tileToAdd->colour == postTile->colour) {
            validMove = true;
            colourMatch = true;
        } else if (tileToAdd->shape == postTile->shape) {
            validMove = true;
            shapeMatch = true;
        }
    } else if (postTile == nullptr) {
        if (tileToAdd->colour == prevTile->colour) {
            validMove = true;
            colourMatch = true;
        } else if (tileToAdd->shape == prevTile->shape) {
            validMove = true;
            shapeMatch = true;
        }
    } else {
        if ((prevTile->colour == tileToAdd->colour &&
                 postTile->colour == tileToAdd->colour)) {
            validMove = true;
            colourMatch = true;
        } else if (prevTile->shape == tileToAdd->shape &&
                             postTile->shape == tileToAdd->shape) {
            validMove = true;
            shapeMatch = true;
        }
    }

    // Checking if line the tile is to be added to is valid
    // same colour, or same shape, and no identical tile
    if (validMove) {
        // To left or above first, then right or down second.
        int adjacentTiles = 0;
        int adjacentTilesB = lineChecker(row, col, -rowAdjustment,
                                        -colAdjustment, shapeMatch,
                                        colourMatch, tileToAdd);
        int adjacentTilesA = lineChecker(row, col, rowAdjustment,
                                         colAdjustment, shapeMatch,
                                         colourMatch, tileToAdd);
        if (adjacentTilesB == -1 || adjacentTilesA == -1) {
            validMove = false;
        } else {
            adjacentTiles = adjacentTilesB + adjacentTilesA;
        }
        // Final check. If number of adjacent tiles in this
        // column is more than 5 then tile cannot be placed.
        if (adjacentTiles > 5) {
            validMove = false;
        }
    }
    return validMove;
}

int Board::lineChecker(int row, int col, int rowAdjustment,
                       int colAdjustment, bool shapeMatch,
                       bool colourMatch, Tile* tile) {
    int adjacentTiles = 0;
    bool validMove = true;
    int currentRow = row + rowAdjustment;
    int currentCol = col + colAdjustment;
    bool adjacentTile = true;
    // Check how many tiles there are in a row.
    while (adjacentTile && validMove) {
        Tile* tileCheck;
        if (currentRow >= rows || currentCol >= cols ||
            currentCol < 0 || currentRow < 0) {
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
