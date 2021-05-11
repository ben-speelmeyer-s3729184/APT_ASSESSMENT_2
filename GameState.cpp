#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};

// Takes a player array, the tileBag, board and numberOfPlayers added to the
// game.
GameState::GameState(Player** players, LinkedList* tileBag, Board* board,
                     int noOfPlayers)
    : players(players),
      tileBag(tileBag),
      board(board),
      noOfPlayers(noOfPlayers) {}

GameState::~GameState(){};

Player** GameState::getPlayers() { return players; }
Board* GameState::getBoard() { return board; }
LinkedList* GameState::getTileBag() { return tileBag; }

// Returns a complete string representation of the gamestate of saving purposes.
std::string GameState::toString() {
  std::string gameData;
  for (int i = 0; i < noOfPlayers; ++i) {
    gameData.append(players[i]->getPlayerName() + "\n");
    gameData.append(std::to_string(players[i]->getPlayerScore()) + "\n");
    gameData.append(players[i]->getPlayerHand());
  }
  gameData.append(tileBag->toString());
  gameData.append(board->boardToString());
  return gameData;
}