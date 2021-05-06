#include "GameEngine.h"

GameEngine::GameEngine(std::string player1Name, std::string player2Name) {
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    gameState = new GameState();
    tileBag = new LinkedList();
    //board = new Boart();
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
            //if playTile works, playerTile = true;
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
    //check tiles surrounding current tile. Check left, right up and down. Tally score
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