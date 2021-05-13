// Copyright 2021
#include "Player.h"

#include <string>

Player::Player(std::string playerName) {
    playerHand = new LinkedList();
    this->playerName = playerName;
    playerScore = 0;
}

Player::~Player() { delete playerHand; }

int Player::handSize() { return playerHand->size(); }
bool Player::hasTile(Tile* tile) {
    return playerHand->contains(tile);
}
void Player::addTileToHand(Tile* tile) { playerHand->addTile(tile); }

Tile* Player::retrieveTile(Tile* tile) {
    return playerHand->getTile(tile);
}
std::string Player::getPlayerName() { return playerName; }

std::string Player::getPlayerHand() { return playerHand->toString(); }

int Player::getPlayerScore() { return playerScore; }

void Player::addScore(int scoreModifier) { playerScore += scoreModifier; }
