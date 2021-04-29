
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
   public:
    Node(Tile* tile, Node* next);
    Node(Node& other);
    ~Node();

    Tile* tile;
    Node* next;

    bool containsTile(Tile* tile);

   private:
};

#endif  // ASSIGN2_NODE_H
