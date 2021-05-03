#include "Hand.h"

Hand::Hand() { this->hand = new LinkedList(); };

Hand::~Hand() { delete hand; };

Tile* Hand::retrieveTile(Tile* tile) {
  Tile* retTile = hand->getTile(tile);
  return retTile;
}

void Hand::addTile(Tile* tile) { hand->addTile(tile); }

std::string Hand::handDetails() { return hand->toString(); }
