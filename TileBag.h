#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"

class TileBag {
 public:
  TileBag();
  TileBag(TileBag& tileBag);
  ~TileBag();

  void addTile(Tile* tile);
  Tile* takeFront();
  int size();
  std::string toString();

 private:
  LinkedList* tileBag;
};

#endif  // TILEBAG_H