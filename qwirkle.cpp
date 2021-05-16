// Copyright 2021
#include <iostream>
#include <string>

#include "Cli.h"

void testGameEngine();
int readShape(char shape);

int main(int argc, char* argv[]) {
    // create CLI object
    bool check = true;
    if (argc >= 2) {
        std::string arg = argv[1];
        if (arg == "static") {
            check = false;
        }
    }
    Cli console(check);

    // print greating
    std::cout << "Welcome to Qwirkle!\n"
                        << "-------------------\n"
                        << std::endl;

    console.printMenu();

    // main loop
    while (!console.runGame()) {
    }

    std::cout << "Goodbye" << std::endl;

    //    testGameEngine();

    return EXIT_SUCCESS;
}