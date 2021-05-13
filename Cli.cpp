// Copyright 2021
#include "Cli.h"

Cli::Cli() {
  gameEngine = new GameEngine(false);
  dataManager = new DataManager();
  gameState = nullptr;
  currentPlayer = nullptr;
  playerNum = 0;
}

Cli::Cli(bool randomSeed) {
  gameEngine = new GameEngine(randomSeed);
  dataManager = new DataManager();
  gameState = nullptr;
  currentPlayer = nullptr;
  playerNum = 0;
}

Cli::~Cli() {
  delete gameEngine;
  delete dataManager;
  delete gameState;
  gameEngine = nullptr;
  dataManager = nullptr;
}

/*
 * Takes the user's input and stores it in buffer.
 * if input is 'quit' (4), then exit is set to true.
 */
bool Cli::nextInput() {
  // initialise input to unaccepted argument
  std::cout << "> ";
  int input = -1;
  std::cin >> input;
  bool inputCheck = input <= 0 || input > 4;
  while (inputCheck) {
    if (input == EOF) {
      inputCheck = false;
    } else if (input <= 0 || input > 4) {
      std::cout << "\nInvalid Input\n" << std::endl;
      std::cout << "> ";
      std::cin >> input;
    } else {
      inputCheck = false;
    }
  }
  // set exit flag for input 4
  if (input == QUIT || input == EOF) {
    exit = true;
  } else if (input == LOAD_GAME) {
    // get filename
    bool gameLoaded = loadGame();
    if (gameLoaded) {
      std::cout << "\nQwirkle game successfully loaded" << std::endl;
      startGameplay();
    } else {
      std::cout << std::endl;
      printMenu();
    }
  } else if (input == CREDITS) {
    printCredits();
  } else if (input == NEW_GAME) {
    exit = newGame();
    if (!exit) {
      std::cout << "\nLet's Play!\n" << std::endl;
      startGameplay();
    }
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

void Cli::startGameplay() {
  // need to clear the cin buffer before
  // starting the gameplay, due to use of
  // getline
  std::cin.ignore(1000, '\n');

  while (nextRound()) {
    std::cout << "> ";
  }
}

bool Cli::newGame() {
  // initialise player names
  std::string player1Name = "";
  std::string player2Name = "";

  // get player info
  std::cout << "Starting a New Game\n" << std::endl;
  std::cout << "Enter a name for player 1 (uppercase characters only)\n> ";

  std::cin >> player1Name;
  bool exitCheck = false;
  bool nameCheck = checkName(player1Name);
  // check name format
  while (!nameCheck) {
    if (std::cin.eof()) {
      nameCheck = true;
      exitCheck = true;
    } else {
      std::cout << "Invalid Input.\n> ";
      std::cin >> player1Name;
      nameCheck = checkName(player1Name);
    }
  }
  if (!exitCheck) {
    std::cout << "Enter a name for player 2 (uppercase characters only)\n> ";

    std::cin >> player2Name;
    nameCheck = checkName(player2Name);
    // check name format
    while (!nameCheck) {
      if (std::cin.eof()) {
        nameCheck = true;
        exitCheck = true;
      } else {
        std::cout << "Invalid Input.\n> ";
        std::cin >> player2Name;
        nameCheck = checkName(player2Name);
      }
    }
    if (!exitCheck) {
      gameEngine->addPlayer(player1Name);
      gameEngine->addPlayer(player2Name);
    }
  }
  return exitCheck;
}
/**
 *loadGame - Loads a game
 */
bool Cli::loadGame() {
  std::string fileName = "";
  if (gameState != nullptr) {
    GameState* toDelete = gameState;
    gameState = nullptr;
    delete toDelete;
  }
  std::cout << "Enter the filename from which load a game\n> ";

  std::cin >> fileName;

  if (std::cin.eof()) {
    exit = true;
  }

  bool gameLoaded = false;

  while (!gameLoaded && !exit) {
    // Tries to load a game. If file cannot be loaded, input is bad.
    gameState = dataManager->loadGame(fileName);
    // Exits on EOF or quit, else checks loadGame, if state exists, loads game.
    if (std::cin.eof() || fileName == "quit") {
      exit = true;
    } else if (gameState == nullptr) {
      std::cout << "Invalid file name.\n> ";
      std::cin >> fileName;
    } else {
      gameEngine->loadGameState(gameState);
      playerNum = gameState->getCurrentPlayer();
      gameLoaded = true;
    }
  }
  return gameLoaded;
}

bool Cli::nextRound() {
  bool status = true;
  printPlayerInfo();

  // parse player input until acceptable value
  while (!parsePlayerInput(*currentPlayer)) {
    std::cout << "Invalid Input\n";
  }
  // if player wants to quit, flag will be set
  if (exit) status = false;

  return status;
}

void Cli::printPlayerInfo() {
  std::string name = "";
  std::string hand = "";

  Player* player1 = gameEngine->getPlayer(0);
  Player* player2 = gameEngine->getPlayer(1);

  if (playerNum == 0) {
    name = player1->getPlayerName();
    hand = player1->getPlayerHand();
    currentPlayer = player1;
  } else {
    name = player2->getPlayerName();
    hand = player2->getPlayerHand();
    currentPlayer = player2;
  }

  std::cout << name << ", it's your turn" << std::endl;
  std::cout << "Score for " << player1->getPlayerName() << ": "
            << player1->getPlayerScore() << std::endl;
  std::cout << "Score for " << player2->getPlayerName() << ": "
            << player2->getPlayerScore() << std::endl;

  std::cout << gameEngine->printBoard() << std::endl;

  std::cout << "Your hand is" << std::endl;
  std::cout << hand << std::endl;
}

void splitString(
    std::vector<std::string>& input,
    std::string words) {  //  Is this a non-const reference? If so, make const
                          //  or use a pointer: std::vector<std::string>& input
                          //  [runtime/references] [2]
  std::string buffer;
  std::string value;
  for (size_t i = 0; i < words.length(); i++) {
    // is the section a space?
    value = words[i];

    // if whitespace or end of line
    if (value == " ") {
      // add to vector
      input.push_back(buffer);

      // clear buffer
      buffer = "";
    } else if (i == words.length() - 1) {
      buffer.append(value);
      // add to vector
      input.push_back(buffer);
    } else {
      // append to buffer
      buffer.append(value);
    }
  }
}

bool Cli::validateTile(std::string tile) {
  bool status = false;
  size_t colourCheck = tileColours.find(tile[0]);
  // current shape codes are 1-6 (ASCII = 49-54)
  if (colourCheck != std::string::npos && tile[1] >= 49 && tile[1] <= 54) {
    status = true;
  }

  return status;
}

bool Cli::validatePosition(std::string position) {
  bool status = false;
  std::vector<int> boardSize;
  boardSize = gameEngine->getBoardSize();

  if (position.length() == 2) {
    // if row letter - 65 (ASCII Capital range) is less than rows,
    // and col number is less than col count, then position is valid

    if (position[0] - 65 < boardSize[0] && position[1] - 48 < boardSize[1]) {
      status = true;
    }
  } else if (position.length() == 3) {
    int col = std::stoi(position.substr(1, 2));
    if (position[0] - 65 < boardSize[0] && col < boardSize[1]) {
      status = true;
    }
  }

  return status;
}

Colour getColour(std::string tile) {
  const char colChar = tile[0];
  Colour col = '\0';

  if (colChar == 'R') {
    col = RED;
  } else if (colChar == 'O') {
    col = ORANGE;
  } else if (colChar == 'Y') {
    col = YELLOW;
  } else if (colChar == 'G') {
    col = GREEN;
  } else if (colChar == 'B') {
    col = BLUE;
  } else if (colChar == 'P') {
    col = PURPLE;
  }
  return col;
}

Shape getShape(std::string tile) {
  const char shpChar = tile[1];
  Shape shp = 0;
  if (shpChar == '1') {
    shp = CIRCLE;
  } else if (shpChar == '2') {
    shp = STAR_4;
  } else if (shpChar == '3') {
    shp = DIAMOND;
  } else if (shpChar == '4') {
    shp = SQUARE;
  } else if (shpChar == '5') {
    shp = STAR_6;
  } else if (shpChar == '6') {
    shp = CLOVER;
  }

  return shp;
}

int parseRow(std::string pos) {
  char rowVal = pos[0];
  return (int)rowVal - 65;  // Using C-style cast.  Use static_cast<int>(...)
                            // instead  [readability/casting] [4]
}

int parseCol(std::string pos) {
  int col = -1;
  if (pos.length() == 2) {
    col = std::stoi(pos.substr(1, 1));
  } else if (pos.length() == 3) {
    col = std::stoi(pos.substr(1, 2));
  }
  return col;
}

bool Cli::parsePlayerInput(Player& player) {
  std::cout << "> ";
  std::vector<std::string> input;
  std::string words;

  // get full command
  std::getline(std::cin, words);
  // convert to vector of strings
  splitString(input, words);

  // parse status, will be false unless
  // acceptable command is given
  bool status = false;
  bool saved = false;
  bool gameFinished = false;
  // Possible commands in gameplay:
  // place XY at XY
  // replace XY
  // save savedGame
  if (input.size() == 4) {
    if (input[0] == "place" && input[2] == "at") {
      if (validateTile(input[1]) && validatePosition(input[3])) {
        Colour colr = getColour(input[1]);
        Shape shp = getShape(input[1]);
        Tile tileToPlace(colr, shp);
        // Tile* tileToPlace = new Tile(colr, shp); TODO, test this!

        int row = parseRow(input[3]);
        int col = parseCol(input[3]);

        bool validMove =
            gameEngine->checkTilePlacement(&player, row, col, &tileToPlace);
        if (validMove) {
          gameFinished = gameEngine->endOfRoundCalculations(&player, row, col,
                                                            &tileToPlace);
          status = true;
        }
      }
    }
  } else if (input.size() == 2) {
    if (input[0] == "replace") {
      if (validateTile(input[1])) {
        Colour colr = getColour(input[1]);
        Shape shp = getShape(input[1]);
        Tile tileToPlace(colr, shp);
        gameEngine->replaceTile(&player, &tileToPlace);
        status = true;
      }
    } else if (input[0] == "save") {
      if (gameState != nullptr) {
        GameState* toDelete = gameState;
        gameState = nullptr;
        delete toDelete;
      }
      gameState = gameEngine->getGameState(playerNum);
      if (dataManager->saveGame(gameState, input[1])) {
        std::cout << "\nGame successfully saved\n" << std::endl;
        status = true;
        saved = true;
      }
    }
  } else if (input.size() == 1) {
    if (input[0] == "quit") {
      exit = true;
      status = true;
    }
  } else if (std::cin.eof()) {
    exit = true;
    status = true;
  }
  if (gameFinished) {
    std::cout << "Game over" << std::endl;
    int scores[gameEngine->getNoOfPlayers()];
    for (int i = 0; i < gameEngine->getNoOfPlayers(); i++) {
      Player player = *gameEngine->getPlayer(i);
      scores[i] = gameEngine->getPlayer(i)->getPlayerScore();
      std::cout << "Score for " << player.getPlayerName() << ": "
                << player.getPlayerScore() << std::endl;
    }
    int highestScore = 0;
    int playerNumber = 0;
    for (int i = 0; i < gameEngine->getNoOfPlayers(); ++i) {
      if (scores[i] > highestScore) {
        highestScore = scores[i];
        playerNumber = i;
      }
    }
    Player* winningPlayer = gameEngine->getPlayer(playerNumber);
    std::cout << "Player " << winningPlayer->getPlayerName() << " won!";
    std::cout << std::endl << std::endl;
    exit = true;
  }
  if (!saved && status) {
    // change current player
    if (playerNum > 0) {
      playerNum = 0;
    } else {
      playerNum = 1;
    }
  }

  return status;
}

bool Cli::checkName(const std::string& name) const {
  // if stringStatus is true, then name is ok
  bool stringStatus = true;
  // avoid zero-length strings
  if (name.length() == 0) {
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
  std::string names[] = {"Matthew Cole", "Finn Gurry", "Sarthak Rungta",
                         "Benjamin Speelmeyer"};
  std::string sNums[] = {"s3489649", "s3431331", "s3816605", "s3729184"};
  for (int i = 0; i < teamCount; i++) {
    std::cout << "Name: " << names[i] << "\n";
    std::cout << "Student ID: " << sNums[i] << "\n";
    std::cout << "Email: " << sNums[i] << "@student.rmit.edu.au\n" << std::endl;
  }
  printMenu();
}
