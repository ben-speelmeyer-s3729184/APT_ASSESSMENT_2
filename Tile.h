
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
   public:
    Tile();
    Tile(Colour colour, Shape shape);
    Tile(Tile& tile);
    std::string toString();
    Colour colour;
    Shape shape;
};

#endif  // ASSIGN2_TILE_H
