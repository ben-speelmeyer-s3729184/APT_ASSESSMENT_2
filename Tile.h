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
    /*
    * Constructor
    */
    Tile(Colour colour, Shape shape);

    /*
    * Copy constructor
    */
    Tile(Tile& tile);

    /*
    * Returns a string representation of Tile
    */
    std::string toString();


    Colour colour;
    Shape shape;
};

#endif  // TILE_H_
