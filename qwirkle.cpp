#include <iostream>

#include "Cli.h"
#include "GameEngine.h"
#include "LinkedList.h"
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

    gameEngine->playTile(1, 3, 3, &tile);
    gameEngine->playTile(2, 3, 4, &tile2);
    gameEngine->playTile(1, 2, 3, &tile3);
    gameEngine->playTile(2, 2, 4, &tile4);
    gameEngine->playTile(1, 2, 5, &tile5);
    gameEngine->printBoard();
    std::cout << gameEngine->toString();
    delete gameEngine;
}