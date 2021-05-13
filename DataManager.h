// Copyright 2021
#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#include "GameState.h"
#include <string>

class DataManager {
 public:
  DataManager();
  static bool saveGame(GameState* saveGame, std::string fileName);
  static GameState* loadGame(std::string fileName);
};

#endif  // DATAMANAGER_H_
