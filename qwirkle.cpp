
#include <iostream>

#include "Cli.h"
#include "GameEngine.h"
#include "LinkedList.h"
#include "Tile.h"
#define EXIT_SUCCESS 0

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
    GameEngine* gameEngine = new GameEngine();
    gameEngine->addPlayer("RANDOM2");
    gameEngine->addPlayer("RANDOM1");
    std::cout << gameEngine->toString();
    delete gameEngine;
    return EXIT_SUCCESS;
}
