#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};
GameState::GameState(Player* players[], LinkedList* tileBag, Board* board,
                     int noOfPlayers)
    : tileBag(tileBag),
      board(board),
      noOfPlayers(noOfPlayers) {
        // populate players
        for (int i = 0; i < noOfPlayers; i++) {
          this->players[i] = players[i];
        }
      }

GameState::GameState(const GameState& other) {
  for (int i = 0; i < other.noOfPlayers; i++) {
    this->players[i] = other.players[i];
  }
  this->tileBag = other.tileBag;
  this->board = other.board;
  this->noOfPlayers = other.noOfPlayers;
}

GameState::~GameState(){};

Player** GameState::getPlayers() { return players; }
Board* GameState::getBoard() { return board; }
LinkedList* GameState::getTileBag() { return tileBag; }

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