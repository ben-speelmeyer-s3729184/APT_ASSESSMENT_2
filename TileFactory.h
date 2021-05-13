// Copyright 2021
#ifndef TILEFACTORY_H_
#define TILEFACTORY_H_

#define MAX_TILE_BAG_SIZE 72
#define TILE_ATTRIBUTES 2
#define COLOUR_IND 0
#define SHAPE_IND 1

typedef char TilesImport[MAX_TILE_BAG_SIZE][TILE_ATTRIBUTES];

#include "LinkedList.h"
#include "Player.h"
#include <string>

class TileFactory {
 public:
  TileFactory();
  LinkedList* createTileBag(bool randomSeed);
  LinkedList* createTileBag(std::string loadedTileBag);
  LinkedList* createHand(std::string hand);

 private:
  void importTileList(TilesImport tiles);
  int readShape(char shape);
};

#endif  // TILEFACTORY_H_
