
#include <iostream>

#include "Cli.h"
#include "LinkedList.h"
#include "Tile.h"
#define EXIT_SUCCESS 0

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

    // delete hand;
    // delete tileBag;
    return EXIT_SUCCESS;
}
