#ifndef ASSIGN2_DATA_MANAGER_H
#define ASSIGN2_DATA_MANAGER_H

#include "GameState.h"

class DataManager {
 private:

 public:
  DataManager();
  static bool saveGame(GameState* saveGame, std::string fileName);
  static GameState* loadGame(std::string fileName);
};

#endif  // ASSIGN2_DATA_MANAGER_H