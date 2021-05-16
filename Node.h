// Copyright 2021
#ifndef NODE_H_
#define NODE_H_

#include "Tile.h"

class Node {
public:
    /*
    * Constructor
    */
    Node(Tile* tile, Node* next);

    /*
    * Copy constructor
    */
    Node(Node& other);

    /*
    * Destructor
    */
    ~Node();

    Tile* tile;
    Node* next;

    /*
    * Check if node contains tile
    */
    bool containsTile(Tile* tile);
};

#endif  // NODE_H_
