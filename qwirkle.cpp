// Copyright 2021
#include <iostream>

#include "Cli.h"
#include "DataManager.h"
#include "GameEngine.h"
#include "GameState.h"
#include "LinkedList.h"
#include "Tile.h"

void testGameEngine();
int readShape(char shape);

int main(void) {
  // create CLI object
  Cli console;

  // print greating
  std::cout << "Welcome to Qwirkle!\n"
            << "-------------------\n"
            << std::endl;

  console.printMenu();

  // main loop
  while (!console.nextInput()) {
  }

  std::cout << "Goodbye" << std::endl;

  //  testGameEngine();

  return EXIT_SUCCESS;
}

// void testGameEngine() {
//   GameEngine* gameEngine = new GameEngine(false);
//   gameEngine->addPlayer("RANDOM1");
//   gameEngine->addPlayer("RANDOM2");

//   bool gameFinished = false;
//   while (!gameFinished) {
//     for (int i = 0; i < MAX_NUM_OF_PLAYERS && !gameFinished; ++i) {
//       std::cout << gameEngine->printBoard() << std::endl;
//       Player* player = gameEngine->getPlayer(i);
//       std::cout << "currentPlayer: " << player->getPlayerName() << std::endl;
//       std::cout << "Score: " << player->getPlayerScore() << std::endl;
//       std::cout << "Select Tile: " << player->getPlayerHand();
//       std::string tile;
//       std::cin >> tile;
//       Tile tileToPlace(tile[0], readShape(tile[1]));
//       std::cout << "Select Location: ";
//       std::string location;
//       std::cin >> location;
//       int row = 0;
//       int col = 0;
//       if (location.length() < 3) {
//         row = (int)location[0] % 32 - 1;  // Using C-style cast.  Use static_cast<int>(...) instead  [readability/casting] [4]
//         col = location[1] - '0';
//         std::cout << row << std::endl;
//         std::cout << col << std::endl;
//       } else {
//         row = (int)location[0] % 32 - 1;  // Using C-style cast.  Use static_cast<int>(...) instead  [readability/casting] [4]
//         int colTens = (location[1] - '0') * 10;
//         int colOnes = location[2] - '0';
//         col = colTens + colOnes;
//       }

//       bool validMove =
//           gameEngine->checkTilePlacement(player, row, col, &tileToPlace);
//       if (validMove) {
//         gameFinished =
//             gameEngine->endOfRoundCalculations(player, row, col, &tileToPlace);
//       } else {
//         gameEngine->replaceTile(player, &tileToPlace);
//       }
//       validMove = false;
//     }
//   }

//   DataManager::saveGame(gameEngine->getGameState(0), "saveFiles/save4.txt");
//   delete gameEngine;
// }

// int readShape(char shape) {
//   int shapeRet = '\0';
//   if (shape == '1') {
//     shapeRet = CIRCLE;
//   } else if (shape == '2') {
//     shapeRet = STAR_4;
//   } else if (shape == '3') {
//     shapeRet = DIAMOND;
//   } else if (shape == '4') {
//     shapeRet = SQUARE;
//   } else if (shape == '5') {
//     shapeRet = STAR_6;
//   } else if (shape == '6') {
//     shapeRet = CLOVER;
//   }
//   return shapeRet;
// }
