#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>

#include "DataManager.h"
#include "GameEngine.h"
#include "GameState.h"

Colour getColour(std::string tile);
Shape getShape(std::string tile);

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
  bool parsePlayerInput(Player& player);

  /*
   * Checks tile given by player
   */
  bool validateTile(std::string tile);

  /*
   * Checks position given by player
   */
  bool validatePosition(std::string position);

 public:
  /*
   * Default Cli Constructor
   */
  Cli();

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
  bool nextInput();

  /*
   * prints out main menu.
   */
  void printMenu() const;
};

#endif