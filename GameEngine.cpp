#include "GameEngine.h"

#include "utils.h"

GameEngine::GameEngine(bool randomSeed) {
  noOfPlayers = 0;
  board = new Board();
  players = new Player*[MAX_NUM_OF_PLAYERS];
  board->resizeBoard(26, 26);
  fillTileBag(randomSeed);
  initialTilePlaced = false;
}

GameEngine::~GameEngine() {
  for (int i = 0; i < noOfPlayers; ++i) {
    delete players[i];
  }
  delete[] players;
  delete tileBag;
  delete board;
}

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
      playedTile = board->checkTilePlacement(tile, row, col, initialTilePlaced);
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
  utils utils;
  utils.updateScores(player, board, row, col, initialTilePlaced);
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
GameState* GameEngine::getGameState() {
  GameState* gameState = new GameState(players, tileBag, board, noOfPlayers);
  return gameState;
}

void GameEngine::loadGameState(GameState* loadedState) {
  Player* playerToDelete = nullptr;
  for (int i = 0; i < noOfPlayers; ++i) {
    delete players[i];
  }
  delete[] players;

  delete playerToDelete;
  Board* boardToDelete = board;
  board = loadedState->getBoard();
  delete boardToDelete;
  LinkedList* tileBagToDelete = tileBag;
  tileBag = loadedState->getTileBag();
  delete tileBagToDelete;
}

bool GameEngine::endOfRoundCalculations(Player* player, int row, int col,
                                        Tile* tile) {
  bool endConditionsMet = false;
  placeTile(player, row, col, tile);
  if (!initialTilePlaced) {
    initialTilePlaced = true;
  }
  updateScore(player, row, col);
  topUpPlayerHand(player);
  if (tileBag->size() == 0 && player->handSize() == 0) {
    player->addScore(6);
    endConditionsMet = true;
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