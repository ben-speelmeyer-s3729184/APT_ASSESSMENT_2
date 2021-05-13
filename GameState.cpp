// Copyright 2021
#include "GameState.h"

#include <string>

#include "TileFactory.h"

// Takes a player array, the tileBag, board and numberOfPlayers added to the
// game.
GameState::GameState(Player** players, LinkedList* tileBag, Board* board,
                     int noOfPlayers, int currentPlayer)
    : tileBag(tileBag),
      board(board),
      noOfPlayers(noOfPlayers),
      currentPlayer(currentPlayer) {
  // populate players
  for (int i = 0; i < noOfPlayers; i++) {
    this->players[i] = players[i];
  }
}

GameState::GameState(const GameState& other)
    : currentPlayer(other.currentPlayer) {
  for (int i = 0; i < other.noOfPlayers; i++) {
    this->players[i] = other.players[i];
  }
  this->tileBag = other.tileBag;
  this->board = other.board;
  this->noOfPlayers = other.noOfPlayers;
}

GameState::~GameState() {
  for (int i = 0; i < noOfPlayers; ++i) {
    delete players[i];
  }
  delete tileBag;
  delete board;
}

int GameState::getCurrentPlayer() { return currentPlayer; }
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
  gameData.append(board->getRows() + "," + board->getCols());
  gameData.append(board->boardToString());
  gameData.append(tileBag->toString());
  gameData.append(players[currentPlayer]->getPlayerName());

  return gameData;
}
