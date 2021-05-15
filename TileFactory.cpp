// Copyright 2021
#include "TileFactory.h"

#include <chrono>  // <chrono> is an unapproved C++11 header.  [build/c++11] [5]
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "utils.h"
TileFactory::TileFactory() {}

TileFactory::~TileFactory() {}

TileBag* TileFactory::createTileBag(bool randomSeed) {
  TileBag* tileBag = new TileBag();
  int tileCount = 0;
  TilesImport tiles;
  importTileList(tiles);
  std::uniform_int_distribution<int> uniform_dist(0, MAX_TILE_BAG_SIZE - 1);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine randomNum(seed);
  std::default_random_engine randomNumStatic(0);

  // creates the random number generator with either a set seed or random seed.
  while (tileCount < MAX_TILE_BAG_SIZE) {
    int randIndex = 0;
    if (randomSeed) {
      randIndex = uniform_dist(randomNum);
    } else {
      randIndex = uniform_dist(randomNumStatic);
    }

    if (tiles[randIndex][COLOUR_IND] != '\0' &&
        tiles[randIndex][SHAPE_IND] != '\0') {
      char tileInfo[TILE_ATTRIBUTES] = {tiles[randIndex][COLOUR_IND],
                                        tiles[randIndex][SHAPE_IND]};
      Tile* tile = createTile(tileInfo);
      tileBag->addTile(tile);
      ++tileCount;
      tiles[randIndex][COLOUR_IND] = '\0';
      tiles[randIndex][SHAPE_IND] = '\0';
    }
  }
  return tileBag;
}

TileBag* TileFactory::createTileBag(std::string loadedTileBag) {
  TileBag* tileBag = new TileBag();
  std::string tileData;
  std::istringstream iss(loadedTileBag);

  while (std::getline(iss, tileData, ',')) {
    char tileInfo[TILE_ATTRIBUTES] = {tileData[COLOUR_IND],
                                      tileData[SHAPE_IND]};
    Tile* tile = createTile(tileInfo);
    tileBag->addTile(tile);
  }
  return tileBag;
}

Hand* TileFactory::createHand(std::string hand) {
  Hand* playerHand = new Hand();
  TileBag* tileBag = createTileBag(hand);
  while (tileBag->size() > 0) {
    Tile* tile = tileBag->takeFront();
    playerHand->addTile(tile);
  }
  delete tileBag;
  return playerHand;
}

void TileFactory::importTileList(TilesImport tiles) {
  std::ifstream file("tileList.txt");
  int numRead = 0;
  while (!file.eof() && numRead < MAX_TILE_BAG_SIZE) {
    file >> tiles[numRead][COLOUR_IND];
    file >> tiles[numRead][SHAPE_IND];
    ++numRead;
  }
  file.close();
}

Tile* TileFactory::createTile(char input[TILE_ATTRIBUTES]) {
  utils utils;
  Colour colour = utils.getColour(input);
  Shape shape = utils.getShape(input);
  Tile* tileToPlace = new Tile(colour, shape);
  return tileToPlace;
}