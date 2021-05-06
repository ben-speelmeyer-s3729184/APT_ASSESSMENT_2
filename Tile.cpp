
#include "Tile.h"

#include <string>

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
};

Tile::Tile(Tile& tile) {
    this->colour = tile.colour;
    this->shape = tile.shape;
}

std::string Tile::toString() {
    return colour + std::to_string(shape);
}