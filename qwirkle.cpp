
#include <iostream>

#include "Hand.h"
#include "LinkedList.h"
#include "Tile.h"
#include "TileBag.h"
#define EXIT_SUCCESS 0

int main(void) {
  Hand* hand = new Hand();
  TileBag* tileBag = new TileBag();

  Tile* tile1 = new Tile(RED, CIRCLE);
  Tile* tile2 = new Tile(BLUE, CIRCLE);
  Tile* tile3 = new Tile(GREEN, DIAMOND);

  tileBag->returnTile(tile1);
  tileBag->returnTile(tile2);
  tileBag->returnTile(tile3);
  // Test

  std::cout << hand->handDetails() << std::endl;
  std::cout << tileBag->tileBagDetails() << std::endl;

  hand->addTile(tileBag->drawTile());
  hand->addTile(tileBag->drawTile());

  std::cout << hand->handDetails() << std::endl;
  std::cout << tileBag->tileBagDetails() << std::endl;
  Tile tile(RED, CIRCLE);
  Tile* tempTile = hand->retrieveTile(&tile);
  tileBag->returnTile(tempTile);

  std::cout << hand->handDetails() << std::endl;
  std::cout << tileBag->tileBagDetails() << std::endl;

  delete hand;
  delete tileBag;
  return EXIT_SUCCESS;
}
