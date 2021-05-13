// Copyright 2021
#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#include <string>

#include "GameState.h"

class DataManager {
 public:
  DataManager();

  /*
   * Saves given gamestate into filename
   */
  static bool saveGame(GameState* saveGame, std::string fileName);

  /*
   * Loads given filename into the gameState object
   */
  static GameState* loadGame(std::string fileName);
};

#endif  // DATAMANAGER_H_
