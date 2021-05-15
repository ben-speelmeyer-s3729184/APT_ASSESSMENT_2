// Copyright 2021
#ifndef TILEFACTORY_H_
#define TILEFACTORY_H_

typedef char TilesImport[MAX_TILE_BAG_SIZE][TILE_ATTRIBUTES];

#include <string>

#include "Hand.h"
#include "Player.h"
#include "TileBag.h"
#include "definitions.h"
class TileFactory {
 public:
  TileFactory();
  ~TileFactory();
  TileBag* createTileBag(bool randomSeed);
  TileBag* createTileBag(std::string loadedTileBag);
  Hand* createHand(std::string hand);
  Tile* createTile(char input[TILE_ATTRIBUTES]);

 private:
  void importTileList(TilesImport tiles);
  int readShape(char shape);
};

#endif  // TILEFACTORY_H_
