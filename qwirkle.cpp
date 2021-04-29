
#include <iostream>

#include "LinkedList.h"

#define EXIT_SUCCESS 0

int main(void) {
  LinkedList* list = new LinkedList();

  // Test
  Tile* tile1 = new Tile(RED, CIRCLE);
  Tile* tile2 = new Tile(ORANGE, STAR_4);
  Tile* tile3 = new Tile(YELLOW, DIAMOND);
  Tile* tile4 = new Tile(GREEN, SQUARE);
  Tile* tile5 = new Tile(BLUE, STAR_6);
  Tile* tile6 = new Tile(PURPLE, CLOVER);

  list->addTile(tile1);
  list->addTile(tile2);
  list->addTile(tile3);
  list->addTile(tile4);
  list->addTile(tile5);
  list->addTile(tile6);
  list->toString();
  list->removeTile(tile1);
  list->removeTile(tile4);
  list->toString();
  list->removeTile(tile2);
  list->removeTile(tile3);
  list->toString();
  list->removeTile(tile6);
  list->removeTile(tile5);
  list->toString();
  Tile* tile = new Tile(RED, CIRCLE);
  list->addTile(tile);
  delete list;
  return EXIT_SUCCESS;
}
