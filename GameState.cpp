#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};
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