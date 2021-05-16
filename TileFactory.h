// Copyright 2021
#ifndef TILEFACTORY_H_
#define TILEFACTORY_H_

#include <string>

#include "Definitions.h"
#include "Hand.h"
#include "Player.h"
#include "TileBag.h"

typedef char TilesImport[MAX_TILE_BAG_SIZE][TILE_ATTRIBUTES];

class TileFactory {
public:
    /*
    * Default constructor
    */
    TileFactory();

    /*
    * Destructor
    */
    ~TileFactory();

    /*
    * Creates a Tilebag, if randomSeed is true,
    * Tilebag order will be random
    */
    TileBag* createTileBag(bool randomSeed);

    /*
    * Creates a Tilebag based on string representation. Used
    * for loading a Tilebag from save file.
    */
    TileBag* createTileBag(std::string loadedTileBag);

    /*
    * Creates a player hand from string of Tiles. Used for
    * loading a Tilebag from save file.
    */
    Hand* createHand(std::string hand);

    /*
    * Creates a tile based on char array
    */
    Tile* createTile(char input[TILE_ATTRIBUTES]);

private:
    /*
    * Creates a list of all Tile Colour and Shape permutations
    */
    void importTileList(TilesImport tiles);

    /*
    * Returns int representation of shape character
    */
    int readShape(char shape);
};

#endif  // TILEFACTORY_H_
