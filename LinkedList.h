// Copyright 2021
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>

#include "Node.h"
#include "Tile.h"

class LinkedList {
public:
    LinkedList();
    LinkedList(LinkedList& list);
    ~LinkedList();

    /*
    * Gets a pointer to specific tile
    */
    Tile* getTile(Tile* tile);

    /*
    * Takes a tile from front of list and returns a pointer to it
    */
    Tile* takeFront();

    /*
    * Add a tile to LinkedList
    */
    void addTile(Tile* tile);


    /*
    * Remove Tile From the tail
    */
    void removeFront();

    /*
    * Remove First instance of tile
    */
    void removeTile(Tile* tile);

    /*
    * Return size of linked List
    */
    int size();

    /*
    * Check for a tile
    */
    bool contains(Tile* tile);

    /*
    * String representation of the linkedList
    */
    std::string toString();

private:
    Node* head;
    Node* tail;
    int count;

    /*
    * Utility function called by destructor
    */
    void clear();
};

#endif  // LINKEDLIST_H_
