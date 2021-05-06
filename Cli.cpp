#include "Cli.h"




/*
* Takes the user's input and stores it in buffer.
* if input is 'quit' (4), then exit is set to true.
*/
bool Cli::nextInput() {

    // initialise input to unaccepted argument
    std::cout << "> ";
    int input = -1;
    std::cin >> input;
    while(input <= 0 || input > 4) {
        std::cout << "\nInvalid input! \nPlease give an answer in the range 1-4:\n" << std::endl;
        std::cout << "> ";
        std::cin >> input;
    }

    // set exit flag for input 4
    if (input==QUIT) {
        exit = true;
    } else if (input==LOAD_GAME) {
        // get filename
        // game.load()
    } else if (input==CREDITS) {
        printCredits();
    } else if (input==NEW_GAME) {
        newGame();
    }
    return exit;
}


void Cli::printMenu() const {

    std::cout << "Menu\n";
    std::cout << "----\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Credits (Show student information)\n";
    std::cout << "4. Quit\n" << std::endl;

    
}


void Cli::newGame() {
    // initialise player names
    std::string player1Name = "";
    std::string player2Name = "";

    // get player info
    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for player 1 (uppercase characters only)\n>";

    std::cin >> player1Name;
    // check name format
    while (!checkName(player1Name)) {
        std::cout << "Invalid name format! Please enter a name with uppercase characters\n>";
        std::cin >> player1Name;
    }

    std::cout << "Enter a name for player 2 (uppercase characters only)\n>";

    std::cin >> player2Name;
    // check name format
    while (!checkName(player2Name)) {
        std::cout << "Invalid name format! Please enter a name with uppercase characters\n>";
        std::cin >> player2Name;
    }
}


bool Cli::checkName(const std::string& name) const {
    // if stringStatus is true, then name is ok
    bool stringStatus = true;
    // avoid zero-length strings
    if (name.length()==0) {
        stringStatus = false;
    }
    // Make sure all values are upper case (ASCII 65-90)
    for (size_t i = 0; i < name.length(); i++) {
        if (name[i] < 65 || name[i] > 90) {
            stringStatus = false;
        }
    }

    return stringStatus;
}

void Cli::printCredits() {
    const int teamCount = 4;
    std::string names[] = {"Matthew Cole", "Finn Gurry", "Sarthak Rungta", "Benjamin Speelmeyer"};
    std::string sNums[] = {"s3489649", "s3431331", "s3816605", "s3729184"};
    for (int i = 0; i < teamCount; i++) {
        std::cout << "Name: " << names[i] << "\n";
        std::cout << "Student ID: " << sNums[i] << "\n";
        std::cout << "Email: " << sNums[i] << "@student.rmit.edu.au\n" << std::endl;
    }
    printMenu();
}