#ifndef UTILS_H
#define UTILS_H

#include "Tile.h"

class utils {
 public:
  Shape getShape(std::string tile);
  Colour getColour(std::string tile);
};

#endif  // UTILS_H