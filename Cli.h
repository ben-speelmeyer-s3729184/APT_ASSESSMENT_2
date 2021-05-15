// Copyright 2021
#ifndef CLI_H_
#define CLI_H_

#define PLAYER_1 0
#define PLAYER_2 1

#include <iostream>
#include <string>
#include <vector>

#include "DataManager.h"
#include "GameEngine.h"
#include "GameState.h"

/*
 * Command line input (CLI) class to assist with processing
 * user input and displaying menu.
 */
class Cli {
 private:
  // status flag for input
  bool exit = false;
  GameEngine* gameEngine;
  DataManager* dataManager;
  GameState* gameState;
  int playerNum = 0;
  const std::string tileColours = "ROYGBP";
  Player* currentPlayer;

  // enum for main menu options, we start at one and the
  // compiler will increment for us
  enum { NEW_GAME = 1, LOAD_GAME, CREDITS, QUIT };

  /*
   * Initialises new game
   */
  bool newGame();

  /*
   * Checks the input player name to make sure it complies with specifications.
   */
  bool checkName(const std::string& name) const;

  /*
   * Print credits with all group member information.
   */
  void printCredits();

  /*
   * Loads a game from user specified file
   */
  bool loadGame();

  /*
   * Starts main gameplay loop
   */
  void startGameplay();

  /*
   * Base gameplay functionality
   */
  bool nextRound();

  /*
   * Prints required info for given player at start of round
   */
  void printPlayerInfo();

  /*
   * Takes user input and parses command
   */
  bool parsePlayerInput(Player* player);

  /*
   * Checks tile given by player
   */
  bool validateTile(std::string tile);

  /*
   * Checks position given by player
   */
  bool validatePosition(std::string position);

  /*
   * Cleans the Game state
   */
  void cleanGameState();

 public:
  /*
   * Seed Cli Constructor
   */
  Cli(bool randomSeed);

  /*
   * Destructor
   */
  ~Cli();

  /*
   * takes input from std::cin and processes game state
   */
  bool runGame();

  /*
   * prints out main menu.
   */
  void printMenu() const;

  std::string getInput();
};

#endif  // CLI_H_
