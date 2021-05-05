#include "Player.h"

#include <string>

Player::Player(std::string playerName) {
  playerHand = new Hand();
  this->playerName = playerName;
  playerScore = 0;
}

Player::~Player() { delete playerHand; }

int Player::handSize() { return playerHand->handSize(); }
bool Player::hasTile(Colour colour, Shape shape) {
  return playerHand->containsTile(colour, shape);
}
void Player::addTileToHand(Tile* tile) { playerHand->addTile(tile); }

Tile* Player::retrieveTile(Tile* tile) {
  return playerHand->retrieveTile(tile);
}
std::string Player::getPlayerName() { return playerName; }

std::string Player::getPlayerHand() { return playerHand->handDetails(); }

int Player::getPlayerScore() { return playerScore; }

void Player::addScore(int scoreModifier) { playerScore += scoreModifier; }