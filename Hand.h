#ifndef HAND_H
#define HAND_H

#include "LinkedList.h"
#define HANDSIZE 6

class Hand {
 public:
  Hand();
  Hand(Hand& hand);
  ~Hand();

  int size();
  bool contains(Tile* tile);
  void addTile(Tile* tile);
  Tile* getTile(Tile* tile);
  std::string toString();
  Tile* takeFront();

 private:
  LinkedList* hand;
};

#endif  // HAND_H