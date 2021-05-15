// Copyright 2021
#include "Cli.h"

#include <ios>
#include <limits>

#include "TileFactory.h"
#include "utils.h"

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

std::string getInput();

/*
 * Takes the user's input and stores it in buffer.
 * if input is 'quit' (4), then exit is set to true.
 */
bool Cli::runGame() {
  // initialise input to unaccepted argument
  std::cout << "> ";
  std::string input = "";
  std::string validInputs = "1234";
  bool inputCheck = true;
  int menuValue = 0;
  input = getInput();
  while (inputCheck && !exit) {
    if ((input.length() != 1 || validInputs.find(input) == std::string::npos) &&
        !exit) {
      std::cout << "\nInvalid Input\n" << std::endl;
      std::cout << "> ";
      input = getInput();
    } else if (input.length() == 1 &&
               validInputs.find(input) != std::string::npos) {
      menuValue = validInputs.find(input);
      inputCheck = false;
    }
  }
  if (!exit) {
    menuValue = std::stoi(input);
  } else {
    menuValue = EOF;
  }

  // set exit flag for input 4
  if (menuValue == QUIT || menuValue == EOF) {
    exit = true;
  } else if (menuValue == LOAD_GAME) {
    // get filename
    bool gameLoaded = loadGame();
    if (gameLoaded) {
      std::cout << "\nQwirkle game successfully loaded" << std::endl;
      startGameplay();
    } else if (!exit) {
      std::cout << std::endl;
      printMenu();
    }
  } else if (menuValue == CREDITS) {
    printCredits();
    printMenu();
  } else if (menuValue == NEW_GAME) {
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
  while (nextRound()) {
  }
}

bool Cli::newGame() {
  // initialise player names
  std::string playerName[MAX_NUM_OF_PLAYERS];
  for (int i = 0; i < MAX_NUM_OF_PLAYERS; ++i) {
    playerName[i] = "";
  }
  // get player info
  std::cout << "Starting a New Game\n" << std::endl;

  int playerCount = 0;
  bool exitCheck = false;
  while (playerCount < MAX_NUM_OF_PLAYERS && !exitCheck) {
    std::cout << "Enter a name for player " << playerCount + 1
              << " (uppercase characters only)\n> ";
    playerName[playerCount] = getInput();
    bool nameCheck = checkName(playerName[playerCount]);
    // check name format
    while (!nameCheck) {
      if (std::cin.eof()) {
        nameCheck = true;
        exitCheck = true;
      } else {
        std::cout << "Invalid Input.\n> ";
        playerName[playerCount] = getInput();
        nameCheck = checkName(playerName[playerCount]);
      }
    }
    playerCount++;
  }
  if (!exitCheck) {
    for (int i = 0; i < MAX_NUM_OF_PLAYERS; ++i) {
      gameEngine->addPlayer(playerName[i]);
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
    cleanGameState();
  }
  std::cout << "Enter the filename from which load a game\n> ";
  bool gameLoaded = false;

  while (!gameLoaded && !exit) {
    // Tries to load a game. If file cannot be loaded, input is bad.
    fileName = getInput();
    gameState = dataManager->loadGame(fileName);
    // Exits on EOF or quit, else checks loadGame, if state exists, loads
    // game.
    if (exit || fileName == "quit") {
      exit = true;
    } else if (gameState == nullptr) {
      std::cout << "Invalid file name.\n> ";

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
  while (!parsePlayerInput(currentPlayer)) {
    std::cout << "Invalid Input\n";
  }
  // if player wants to quit, flag will be set
  if (exit) status = false;

  return status;
}

void Cli::printPlayerInfo() {
  std::string name = "";
  std::string hand = "";
  Player* players[MAX_NUM_OF_PLAYERS];
  for (int i = 0; i < MAX_NUM_OF_PLAYERS; ++i) {
    players[i] = gameEngine->getPlayer(i);
  }
  currentPlayer = gameEngine->getPlayer(playerNum);
  name = players[playerNum]->getPlayerName();
  hand = players[playerNum]->getPlayerHand();

  std::cout << name << ", it's your turn" << std::endl;
  for (int i = 0; i < MAX_NUM_OF_PLAYERS; ++i) {
    std::cout << "Score for " << players[i]->getPlayerName() << ": "
              << players[i]->getPlayerScore() << std::endl;
  }
  std::cout << gameEngine->printBoard() << std::endl;

  std::cout << "Your hand is" << std::endl;
  std::cout << hand << std::endl;
}

void splitString(std::vector<std::string>& input, std::string words) {
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
  utils utils;
  Colour colour = utils.getColour(tile);
  Shape shape = utils.getShape(tile);
  bool status = false;
  if (colour != '\0' && shape != 0) {
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

int parseRow(std::string pos) {
  char rowVal = pos[0];
  return static_cast<int>(rowVal - 65);
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

bool Cli::parsePlayerInput(Player* player) {
  std::cout << "> ";
  std::vector<std::string> input;
  std::string words;

  // get full command
  words = getInput();
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
  utils utils;
  if (input.size() == 4) {
    if (input[0] == "place" && input[2] == "at") {
      if (validateTile(input[1]) && validatePosition(input[3])) {
        Colour colr = utils.getColour(input[1]);
        Shape shp = utils.getShape(input[1]);
        Tile tileToPlace(colr, shp);
        // Tile* tileToPlace = new Tile(colr, shp); TODO, test this!

        int row = parseRow(input[3]);
        int col = parseCol(input[3]);

        bool validMove =
            gameEngine->checkTilePlacement(player, row, col, &tileToPlace);
        if (validMove) {
          gameFinished = gameEngine->endOfRoundCalculations(player, row, col,
                                                            &tileToPlace);
          status = true;
        }
      }
    }
  } else if (input.size() == 2) {
    if (input[0] == "replace") {
      if (validateTile(input[1])) {
        Colour colr = utils.getColour(input[1]);
        Shape shp = utils.getShape(input[1]);
        Tile tileToPlace(colr, shp);
        gameEngine->replaceTile(player, &tileToPlace);
        status = true;
      }
    } else if (input[0] == "save") {
      if (gameState != nullptr) {
        cleanGameState();
      }
      gameState = gameEngine->getGameState(playerNum);
      if (dataManager->saveGame(gameState, input[1])) {
        std::cout << "\nGame successfully saved\n" << std::endl;
        status = true;
        saved = true;
      } else {
        std::cout << "\n Save game filed." << std::endl;
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
      Player* player = gameEngine->getPlayer(i);
      scores[i] = player->getPlayerScore();
      std::cout << "Score for " << player->getPlayerName() << ": "
                << player->getPlayerScore() << std::endl;
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
    ++playerNum;
    if (playerNum >= MAX_NUM_OF_PLAYERS) {
      playerNum = 0;
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
}

std::string Cli::getInput() {
  std::string input = "";
  std::getline(std::cin, input);
  if (std::cin.eof()) {
    exit = true;
  }
  return input;
}

void Cli::cleanGameState() {
  GameState* toDelete = gameState;
  gameState = nullptr;
  delete toDelete;
}