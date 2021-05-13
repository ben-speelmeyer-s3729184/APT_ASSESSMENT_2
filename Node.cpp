// Copyright 2021
#include "Node.h"

Node::Node(Tile* tile, Node* next) {
    this->tile = tile;
    this->next = next;
}

Node::Node(Node& other) {
    this->tile = new Tile(*other.tile);
    this->next = other.next;
}

Node::~Node() {
    delete tile;
}

bool Node::containsTile(Tile* check) {
    bool shapeMatch = this->tile->shape == check->shape;
    bool colourMatch = this->tile->colour == check->colour;
    return shapeMatch && colourMatch;
}
