#ifndef ASSIGN2_DATA_MANAGER_H
#define ASSIGN2_DATA_MANAGER_H

#include "GameState.h"

class DataManager {
 public:
  static bool saveGame(GameState* saveGame);
  static GameState* loadGame(std::string fileName);
};

#endif  // ASSIGN2_DATA_MANAGER_H