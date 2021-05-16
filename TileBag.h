#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"

class TileBag {
public:
    /*
    * Default constructor
    */
    TileBag();

    /*
    * Copy constructor
    */
    TileBag(TileBag& tileBag);

    /*
    * Destructor
    */
    ~TileBag();

    /*
    * Adds given tile to Tilebag
    */
    void addTile(Tile* tile);

    /*
    * Removes tile from front of bag and returns a pointer to it
    */
    Tile* takeFront();

    /*
    * Returns Tilebag size
    */
    int size();

    /*
    * Returns a string representation of Tilebag
    */
    std::string toString();

private:
    LinkedList* tileBag;
};

#endif  // TILEBAG_H