#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "LinkedList.h"
#include "Tile.h"

class TileBag {
 public:
  TileBag();
  ~TileBag();

  Tile* drawTile();
  void returnTile(Tile* tile);
  std::string tileBagDetails();

 private:
  LinkedList* tileBag;
};

#endif  // ASSIGN2_TILEBAG_H