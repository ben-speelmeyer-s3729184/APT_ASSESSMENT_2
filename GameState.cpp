#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};
GameState::GameState(Player** players, LinkedList* tileBag, Board* board)
    : players(players), tileBag(tileBag), board(board) {}

GameState::~GameState(){};

Player** GameState::getPlayers() { return players; }
Board* GameState::getBoard() { return board; }
LinkedList* GameState::getTileBag() { return tileBag; }