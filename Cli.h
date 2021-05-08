#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>

#include "GameState.h"

/*
 * Command line input (CLI) class to assist with processing
 * user input and displaying menu.
 */
class Cli {
 private:
  // status flag for input
  bool exit = false;
  GameState game;

  // enum for main menu options, we start at one and the
  // compiler will increment for us
  enum { NEW_GAME = 1, LOAD_GAME, CREDITS, QUIT };

  /*
   * Initialises new game
   */
  void newGame();

  /*-GameS
   * Checks the input player name to make sure it complies with specifications.
   */
  bool checkName(const std::string& name) const;

  /*
   * Print credits with all group member information.
   */
  void printCredits();

 public:
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