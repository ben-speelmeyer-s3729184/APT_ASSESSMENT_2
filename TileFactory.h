#ifndef ASSIGN2_TILE_FACTORY_H
#define ASSIGN2_TILE_FACTORY_H

#define MAX_TILE_BAG_SIZE 72
#define TILE_ATTRIBUTES 2
#define SHAPE_IND 0
#define COLOUR_IND 1

typedef char TilesImport[MAX_TILE_BAG_SIZE][TILE_ATTRIBUTES];

#include "LinkedList.h"

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

#endif  //ASSIGN2_TILE_FACTORY_H