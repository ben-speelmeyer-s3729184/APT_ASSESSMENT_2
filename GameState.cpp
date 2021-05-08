#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};
GameState::GameState(Player* player1, Player* player2, LinkedList* tileBag,
                     Board* board)
    : player1(player1), player2(player2), tileBag(tileBag), board(board) {}

GameState::~GameState(){};

Player* GameState::getPlayer1() { return player1; }
Player* GameState::getPlayer2() { return player2; }
Board* GameState::getBoard() { return board; }
LinkedList* GameState::getTileBag() { return tileBag; }