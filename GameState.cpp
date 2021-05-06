#include "GameState.h"

#include "TileFactory.h"

GameState::GameState(){};
GameState::GameState(Player* player1, Player* player2, Board* board, LinkedList* tileBag)
    : player1(player1), player2(player2), board(board), tileBag(tileBag) {}

GameState::~GameState(){};

void GameState::initiatePlayer1(LinkedList* hand, std::string name, int score) {
    player1 = new Player(name);
    player1->addScore(score);
    for (int i = 0; i < hand->size(); ++i) {
        player1->addTileToHand(hand->takeFront());
    }
}

void GameState::initiatePlayer2(LinkedList* hand, std::string name, int score) {
    player2 = new Player(name);
    player2->addScore(score);
    for (int i = 0; i < hand->size(); ++i) {
        player1->addTileToHand(hand->takeFront());
    }
}

void GameState::initiateBoard(std::string boardInfo) {
}

void GameState::initiateTileBag(std::string tileBagInfo) {
    TileFactory tileFactory;
    tileBag = tileFactory.createTileBag(tileBagInfo);
}

Player* GameState::getPlayer1() {
    return player1;
}
Player* GameState::getPlayer2() {
    return player2;
}
Board* GameState::getBoard() {
    return board;
}
LinkedList* GameState::getTileBag() {
    return tileBag;
}

void GameState::load(std::string fileName) {
}