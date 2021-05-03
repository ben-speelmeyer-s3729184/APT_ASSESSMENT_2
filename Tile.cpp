
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
};

Tile::Tile(Tile& tile) {
    this->colour = tile.colour;
    this->shape = tile.shape;
}
