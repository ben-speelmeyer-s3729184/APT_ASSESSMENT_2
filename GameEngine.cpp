#include "GameEngine.h"

GameEngine::GameEngine(bool randomSeed) {
    noOfPlayers = 0;
    gameState = new GameState();
    board = new Board();
    board->resizeBoard(25, 25);
    fillTileBag(randomSeed);
    initialTilePlaced = false;
}

GameEngine::GameEngine(std::string fileName) {
}

GameEngine::~GameEngine() {
    delete player1;
    delete player2;
    delete tileBag;
    delete gameState;
    delete board;
}

// Initialise the board, players, tileBags, and fill hands and tileBag with
// tiles.
void GameEngine::fillTileBag(bool randomSeed) {
    TileFactory tileFactory;
    tileBag = tileFactory.createTileBag(randomSeed);
}

bool GameEngine::playTile(int currentPlayer, int row, int col, Tile* tile) {
    bool playedTile = false;
    Player* player = nullptr;
    if (currentPlayer == 1) {
        player = player1;
    } else if (currentPlayer == 2) {
        player = player2;
    }
    if (player != nullptr) {
        if (player->hasTile(tile)) {
            if (board->getTile(row, col) == nullptr) {
                bool adjacentTiles = checkForAdjacency(row, col);
                if (initialTilePlaced && adjacentTiles) {
                    bool leftRightCheck = checkLeftRightTiles(row, col, tile);
                    bool upDownCheck = checkUpDownTiles(row, col, tile);
                    if (leftRightCheck && upDownCheck) {
                        board->addTile(tile, row, col);
                    }
                    updateScore(player, col, row);
                } else if (!initialTilePlaced) {
                    bool leftRightCheck = checkLeftRightTiles(row, col, tile);
                    bool upDownCheck = checkUpDownTiles(row, col, tile);
                    if (leftRightCheck && upDownCheck) {
                        board->addTile(tile, row, col);
                    }
                    updateScore(player, col, row);
                    initialTilePlaced = true;
                }
            }
        }
    }
    return playedTile;
}

bool GameEngine::replaceTile(int currentPlayer, Tile* tile) {
    Player* player = nullptr;
    bool tileExists = false;
    if (currentPlayer == 1) {
        player = player1;
    } else if (currentPlayer == 2) {
        player = player2;
    }
    if (player != nullptr) {
        tileExists = player->hasTile(tile);
        if (tileExists) {
            Tile* tileToReplace = player->retrieveTile(tile);
            tileBag->addTile(tileToReplace);
            player->addTileToHand(tileBag->takeFront());
        }
    }
    return tileExists;
}

bool GameEngine::addPlayer(std::string name) {
    bool playerAdded = false;
    if (noOfPlayers == 0) {
        player1 = new Player(name);
        topUpPlayerHand(player1);
        ++noOfPlayers;
        playerAdded = true;
    } else if (noOfPlayers == 1) {
        player2 = new Player(name);
        topUpPlayerHand(player2);
        playerAdded = true;
    }
    return playerAdded;
}

void GameEngine::updateScore(Player* player, int col, int row) {
}

void GameEngine::updateGameState() {
}

GameState* GameEngine::retrieveGameState() {
    return gameState;
}

void GameEngine::topUpPlayerHand(Player* player) {
    while (player->handSize() < HANDSIZE) {
        Tile* tile = tileBag->takeFront();
        player->addTileToHand(tile);
    }
}

bool GameEngine::checkLeftRightTiles(int row, int col, Tile* tile) {
    bool validMove = false;
    Tile* leftTile = board->getTile(row, col - 1);
    Tile* rightTile = board->getTile(row, col + 1);

    //check whether tile to be added can be placed between
    //the positions to the left and right.
    if (leftTile == nullptr && rightTile == nullptr) {
        validMove = true;
    } else if (leftTile == nullptr) {
        if (tile->colour == rightTile->colour || tile->shape == rightTile->shape) {
            validMove = true;
        }
    } else if (rightTile == nullptr) {
        if (tile->colour == leftTile->colour || tile->shape == leftTile->shape) {
            validMove = true;
        }
    } else {
        if ((leftTile->colour == tile->colour && rightTile->colour == tile->colour) ||
            (leftTile->shape == tile->shape && rightTile->shape == tile->shape)) {
            validMove = true;
        }
    }
    //If a tile can be placed next to the adjacent left and right tiles, checks if placing this tile will
    //create a line greater than 6 tiles in this position. If no, then a valid move is confirmed.
    if (validMove) {
        int adjacentTiles = 0;
        bool adjacentTile = true;
        int currentCol = col - 1;
        //Checks to left of chosen position first.
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
        //Final check. If number of adjacent tiles in this column is more than 5
        //then tile cannot be placed.
        if (adjacentTiles > 5) {
            validMove = false;
        }
    }
    return validMove;
}

bool GameEngine::checkUpDownTiles(int row, int col, Tile* tile) {
    bool validMove = false;
    Tile* upTile = board->getTile(row - 1, col);
    Tile* downTile = board->getTile(row + 1, col);
    //check whether tile to be added can be placed between
    //the positions above and below chosen position.
    if (upTile == nullptr && downTile == nullptr) {
        validMove = true;

    } else if (upTile == nullptr) {
        if (tile->colour == downTile->colour || tile->shape == downTile->shape) {
            validMove = true;
        }
    } else if (downTile == nullptr) {
        if (tile->colour == upTile->colour || tile->shape == upTile->shape) {
            validMove = true;
        }
    } else {
        if ((upTile->colour == tile->colour && downTile->colour == tile->colour) ||
            (upTile->shape == tile->shape && downTile->shape == tile->shape)) {
            validMove = true;
        }
    }
    //If a tile can be placed next to any adjacent tiles, checks if placing this tile will
    //create a line greater than 6 tiles in this position. If no, then a valid move is confirmed.
    if (validMove) {
        int adjacentTiles = 0;
        bool adjacentTile = true;

        //Checks rows above current position first.
        int currentRow = row - 1;
        while (adjacentTile) {
            if (board->getTile(currentRow, col) != nullptr) {
                --currentRow;
                ++adjacentTiles;
            } else {
                adjacentTile = false;
            }
        }
        //Checks rows below current position.
        currentRow = col + 1;
        adjacentTile = true;
        while (adjacentTile) {
            if (board->getTile(currentRow, col) != nullptr) {
                ++currentRow;
                ++adjacentTiles;
            } else {
                adjacentTile = false;
            }
        }
        //Final check. If number of adjacent tiles in this column is more than 5
        //then tile cannot be placed.
        if (adjacentTiles > 5) {
            validMove = false;
        }
    }
    return validMove;
}

bool GameEngine::checkForAdjacency(int row, int col) {
    bool tileAdjacent = false;
    if (board->getTile(row - 1, col) != nullptr || board->getTile(row + 1, col) != nullptr || board->getTile(row, col - 1) != nullptr || board->getTile(row, col + 1) != nullptr) {
        tileAdjacent = true;
    }
    return tileAdjacent;
}

void GameEngine::printBoard() {
    board->printBoard();
}

std::string GameEngine::toString() {
    std::string gameData;
    gameData.append(player1->getPlayerName() + "\n");
    gameData.append(std::to_string(player1->getPlayerScore()) + "\n");
    gameData.append(player1->getPlayerHand());
    gameData.append(player2->getPlayerName() + "\n");
    gameData.append(std::to_string(player1->getPlayerScore()) + "\n");
    gameData.append(player2->getPlayerHand());
    gameData.append(tileBag->toString());
    gameData.append(board->boardToString());
    return gameData;
}