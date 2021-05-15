// Copyright 2021
#ifndef TILE_H_
#define TILE_H_

#include <string>

#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
 public:
  Tile(Colour colour, Shape shape);
  Tile(Tile& tile);  // Is this a non-const reference? If so, make const or use a pointer: Tile& tile  [runtime/references] [2]
  std::string toString();
  Colour colour;
  Shape shape;
};

#endif  // TILE_H_
