#include "Hand.h"

Hand::Hand() { hand = new LinkedList(); }
Hand::Hand(Hand& hand) { this->hand = new LinkedList(*hand.hand); }

Hand::~Hand() { delete hand; }

int Hand::size() { return hand->size(); }
bool Hand::contains(Tile* tile) { return hand->contains(tile); }
void Hand::addTile(Tile* tile) { hand->addTile(tile); }
Tile* Hand::getTile(Tile* tile) { return hand->getTile(tile); }
Tile* Hand::takeFront() { return hand->takeFront(); }
std::string Hand::toString() { return hand->toString(); }