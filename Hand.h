#ifndef HAND_H
#define HAND_H

#include "Definitions.h"
#include "LinkedList.h"

class Hand {
public:
    /*
    * Default constructor
    */
    Hand();

    /*
    * Copy constructor
    */
    Hand(Hand& hand);

    /*
    * Destructor
    */
    ~Hand();

    /*
    * Returns hand size
    */
    int size();

    /*
    * Checks if tile is in hand, returns true if tile is found
    */
    bool contains(Tile* tile);

    /*
    * Adds a tile to hand
    */
    void addTile(Tile* tile);

    /*
    * Returns pointer to tile in player hand
    */
    Tile* getTile(Tile* tile);

    /*
    * Returns string representation of Hand object
    */
    std::string toString();

    /*
    * Pulls the first tile from the hand and removes from hand
    */
    Tile* takeFront();

private:
    LinkedList* hand;
};

#endif  // HAND_H

