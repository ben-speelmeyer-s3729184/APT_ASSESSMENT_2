// Copyright 2021
#ifndef TILEFACTORY_H_
#define TILEFACTORY_H_

#define MAX_TILE_BAG_SIZE 72
#define TILE_ATTRIBUTES 2
#define COLOUR_IND 0
#define SHAPE_IND 1

typedef char TilesImport[MAX_TILE_BAG_SIZE][TILE_ATTRIBUTES];

#include <string>

#include "Hand.h"
#include "Player.h"
#include "TileBag.h"

class TileFactory {
 public:
  TileFactory();
  ~TileFactory();
  TileBag* createTileBag(bool randomSeed);
  TileBag* createTileBag(std::string loadedTileBag);
  Hand* createHand(std::string hand);
  Tile* createTile(std::string input);

 private:
  void importTileList(TilesImport tiles);
  int readShape(char shape);
};

#endif  // TILEFACTORY_H_
