// Copyright 2021
#include "GameEngine.h"

#include <string>
#include <vector>

#include "ScoreManager.h"

GameEngine::GameEngine(bool randomSeed) {
    noOfPlayers = 0;
    board = new Board();
    board->resizeBoard(26, 26);
    fillTileBag(randomSeed);
    initialTilePlaced = false;
    players = new Player*[MAX_NUM_OF_PLAYERS];
}

GameEngine::~GameEngine() { this->clear(); }

// Initialise the board, players, tileBags, and fill hands and tileBag with
// tiles.
void GameEngine::fillTileBag(bool randomSeed) {
    TileFactory tileFactory;
    tileBag = tileFactory.createTileBag(randomSeed);
}

bool GameEngine::checkTilePlacement(Player* player, int row, int col,
                                    Tile* tile) {
    bool playedTile = false;
    if (player != nullptr) {
        if (player->hasTile(tile)) {
            if (col >= 0 && row >= 0 && col < board->getCols() &&
                    row < board->getRows()) {
                playedTile =
                        board->checkTilePlacement(tile, row,
                                                  col, initialTilePlaced);
            }
        }
    }
    return playedTile;
}

void GameEngine::placeTile(Player* player, int row, int col, Tile* tile) {
    Tile* tileFromHand = player->retrieveTile(tile);
    board->addTile(tileFromHand, row, col);
}

bool GameEngine::replaceTile(Player* player, Tile* tile) {
    bool tileExists = false;
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
    if (true) {
        players[noOfPlayers] = new Player(name);
        topUpPlayerHand(players[noOfPlayers]);
        playerAdded = true;
        ++noOfPlayers;
    }
    return playerAdded;
}

void GameEngine::updateScore(Player* player, int row, int col) {
    ScoreManager scoreManager;
    scoreManager.updateScores(player, board, row, col, initialTilePlaced);
}

int GameEngine::getNoOfPlayers() { return noOfPlayers; }

Player* GameEngine::getPlayer(int playerNumber) {
    Player* playerToReturn = nullptr;
    if (playerNumber < MAX_NUM_OF_PLAYERS) {
        playerToReturn = players[playerNumber];
    }
    return playerToReturn;
}

// Need to update to return a deep copy.
GameState* GameEngine::getGameState(int currentPlayer) {
    GameState* gameState =
            new GameState(players, tileBag, board, noOfPlayers, currentPlayer);
    return gameState;
}
// Clears current game state and loads a previously saved game.
void GameEngine::loadGameState(GameState* loadedState) {
    clear();
    noOfPlayers = loadedState->getNoOfPlayers();
    players = new Player*[noOfPlayers];
    for (int i = 0; i < noOfPlayers; ++i) {
        players[i] = new Player(*loadedState->getPlayers()[i]);
    }
    board = new Board(*loadedState->getBoard());
    tileBag = new TileBag(*loadedState->getTileBag());
    currPlayer = loadedState->getCurrentPlayer();
    if (board->boardToString() == "\n") {
        initialTilePlaced = true;
    }
}

// Places a tile, updates player score, tops up the players hand then checks
// whether a player has triggered the end of game conditions.
bool GameEngine::endOfRoundCalculations(Player* player, int row, int col,
                                        Tile* tile) {
    bool endConditionsMet = false;
    placeTile(player, row, col, tile);
    updateScore(player, row, col);
    topUpPlayerHand(player);
    if (tileBag->size() == 0 && player->handSize() == 0) {
        player->addScore(6);
        endConditionsMet = true;
    }
    if (!initialTilePlaced) {
        initialTilePlaced = true;
    }
    return endConditionsMet;
}

void GameEngine::topUpPlayerHand(Player* player) {
    while (player->handSize() < HANDSIZE && tileBag->size() > 0) {
        Tile* tile = tileBag->takeFront();
        player->addTileToHand(tile);
    }
}

std::string GameEngine::printBoard() { return board->printBoard(); }

std::vector<int> GameEngine::getBoardSize() {
    int rows = 0, cols = 0;
    rows = board->getRows();
    cols = board->getCols();
    return std::vector<int>({rows, cols});
}

void GameEngine::clear() {
    for (int i = 0; i < noOfPlayers; ++i) {
        delete players[i];
    }
    delete[] players;
    delete tileBag;
    tileBag = nullptr;
    delete board;
    board = nullptr;
    noOfPlayers = 0;
    currPlayer = 0;
}