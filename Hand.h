#ifndef ASSIGN2_HAND_H
#define ASSIGN2_HAND_H

#include "LinkedList.h"
#include "Tile.h"

class Hand {
 public:
  Hand();
  ~Hand();

  Tile* retrieveTile(Tile* tile);
  void addTile(Tile* tile);
  std::string handDetails();
  int handSize();

 private:
  LinkedList* hand;
};

#endif  // ASSIGN2_HAND_H
