// Copyright 2021
#ifndef NODE_H_
#define NODE_H_

#include "Tile.h"

class Node {
 public:
    Node(Tile* tile, Node* next);
    Node(Node& other);  //  Is this a non-const reference? If so, make const or use a pointer: Node& other  [runtime/references] [2]
    ~Node();

    Tile* tile;
    Node* next;

    bool containsTile(Tile* tile);

 private:
};

#endif  // NODE_H_
