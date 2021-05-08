#include <iostream>

#include "Cli.h"
#include "GameEngine.h"
#include "LinkedList.h"
#include "SaveLoad.h"
#include "Tile.h"
#define EXIT_SUCCESS 0

void testGameEngine();

int main(void) {
  // create CLI object
  // Cli console;

  // // print greating
  // std::cout << "Welcome to Qwirkle!\n"
  //           << "-------------------\n"
  //           << std::endl;

  // console.printMenu();

  // // main loop
  // while (!console.nextInput()) {
  // }

  // std::cout << "Goodbye" << std::endl;

  // // delete hand;
  // // delete tileBag;
  testGameEngine();

  return EXIT_SUCCESS;
}

void testGameEngine() {
  GameEngine* gameEngine = new GameEngine(false);
  gameEngine->addPlayer("RANDOM1");
  gameEngine->addPlayer("RANDOM2");
  Tile tile(RED, CIRCLE);
  Tile tile2(BLUE, CIRCLE);
  Tile tile4(BLUE, CLOVER);
  Tile tile3(BLUE, CIRCLE);
  Tile tile5(YELLOW, 4);
  Tile tile6(BLUE, 2);
  Player* player = gameEngine->getPlayer(0);

  bool validMove = false;

  gameEngine->checkTilePlacement(player, 1, 0, &tile);
  gameEngine->endOfRoundCalculations(player, 1, 0, &tile);
  player = gameEngine->getPlayer(1);
  validMove = gameEngine->checkTilePlacement(player, 0, 0, &tile2);
  if (validMove) gameEngine->endOfRoundCalculations(player, 0, 0, &tile2);
  player = gameEngine->getPlayer(0);
  validMove = gameEngine->checkTilePlacement(player, 1, 1, &tile3);
  if (validMove) gameEngine->endOfRoundCalculations(player, 1, 1, &tile3);
  player = gameEngine->getPlayer(1);
  validMove = gameEngine->checkTilePlacement(player, 0, 1, &tile4);
  if (validMove) gameEngine->endOfRoundCalculations(player, 0, 1, &tile4);
  player = gameEngine->getPlayer(0);
  validMove = gameEngine->checkTilePlacement(player, 0, 2, &tile5);
  if (validMove) gameEngine->endOfRoundCalculations(player, 0, 2, &tile5);
  player = gameEngine->getPlayer(1);
  validMove = gameEngine->checkTilePlacement(player, 2, 1, &tile6);
  if (validMove) gameEngine->endOfRoundCalculations(player, 2, 1, &tile6);
  std::cout << gameEngine->printBoard();
  std::cout << gameEngine->toString();
  delete gameEngine;
}