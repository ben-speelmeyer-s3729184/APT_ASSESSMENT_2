#include "Player.h"

#include <string>

Player::Player(std::string playerName) {
    playerHand = new Hand();
    this->playerName = playerName;
}

Player::~Player() {
    delete playerHand;
}

int Player::handSize() {
    playerHand->handSize();
}
bool Player::hasTile(Colour colour, Shape shape) {
    return playerHand->containsTile(colour, shape);
}
void Player::addTileToHand(Tile* tile) {
    playerHand->addTile(tile);
}

Tile* Player::playTile(Tile* tile) {
    return playerHand->retrieveTile(tile);
}
std::string Player::playerDetails() {}