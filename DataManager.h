// Copyright 2021
#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#define NUMBER_OF_DATA_ENTRIES 10
#define PLAYER_1_NAME loadedData[0]
#define PLAYER_1_SCORE loadedData[1]
#define PLAYER_1_HAND loadedData[2]
#define PLAYER_2_NAME loadedData[3]
#define PLAYER_2_SCORE loadedData[4]
#define PLAYER_2_HAND loadedData[5]
#define BOARD_SIZE loadedData[6]
#define BOARD_DETAILS loadedData[7]
#define TILE_BAG_DETAILS loadedData[8]
#define CURRENT_PLAYER_NAME loadedData[9]

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

 private:
};

#endif  // DATAMANAGER_H_
