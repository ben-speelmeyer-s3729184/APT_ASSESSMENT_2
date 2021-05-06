#include "GameEngine.h"

GameEngine::GameEngine(std::string player1Name, std::string player2Name) {
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    gameState = new GameState();
    tileBag = new LinkedList();
    board = new Board();
}
GameEngine::~GameEngine() {
    delete player1;
    delete player2;
    delete gameState;
}

// Initialise the board, players, tileBags, and fill hands and tileBag with
// tiles.
void GameEngine::initialiseGame() {
    //Add tiles to tile bag.
    //Add tiles to player hands.
    topUpPlayerHand(player1);
    topUpPlayerHand(player2);
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
            if (board->getTile(row, col) != nullptr) {
                bool leftRightCheck = checkLeftRightTiles(row, col, tile);
                bool upDownCheck = checkUpDownTiles(row, col, tile);
                if (leftRightCheck && upDownCheck) {
                    board->addTile(tile, row, col);
                }
            }
            {
                updateScore(player, col, row);
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
            Tile* tile = player->retrieveTile(tile);
            tileBag->addTile(tile);
            player->addTileToHand(tileBag->takeFront());
        }
    }
    return tileExists;
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
    if (validMove) {
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
    //the positions to the left and right.
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
    if (validMove) {
        int adjacentTiles = 0;
        bool adjacentTile = true;
        int currentRow = row - 1;
        while (adjacentTile) {
            if (board->getTile(currentRow, col) != nullptr) {
                --currentRow;
                ++adjacentTiles;
            } else {
                adjacentTile = false;
            }
        }
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
        if (adjacentTiles > 5) {
            validMove = false;
        }
    }
}