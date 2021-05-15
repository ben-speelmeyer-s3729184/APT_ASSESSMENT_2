// Copyright 2021
#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <string>
#include <vector>

#include "Board.h"
#include "Definitions.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "TileBag.h"
#include "TileFactory.h"
class GameEngine {
 public:
  GameEngine(bool randomSeed);  // Single-parameter constructors should be
                                // marked explicit.  [runtime/explicit] [5]
  ~GameEngine();

  // Game setup functions
  bool addPlayer(std::string name);
  GameState* getGameState(int currentPlayer);
  void loadGameState(GameState* loadedState);

  // Tile placement functions
  bool checkTilePlacement(Player* player, int row, int col, Tile* tile);
  bool replaceTile(Player* player, Tile* tile);
  bool checkTilePlaceability(int row, int col, Tile* tile);

  // Perform end of round routines, place tile, calculate score, top up hand and
  // check win conditions.
  bool endOfRoundCalculations(Player* player, int row, int col, Tile* tile);

  Player* getPlayer(int playerNumber);
  int getNoOfPlayers();

  // Board Details
  std::string printBoard();

  std::vector<int> getBoardSize();

 private:
  bool initialTilePlaced;
  Player** players;
  int noOfPlayers;
  int currPlayer = 0;
  TileBag* tileBag;
  Board* board;
  void clear();
  void placeTile(Player* player, int row, int col, Tile* tile);
  void topUpPlayerHand(Player* player);
  void updateScore(Player* player, int col, int row);
  bool checkForAdjacency(int row, int col);
  bool checkAdjacentTiles(int row, int rowAdjustment, int col,
                          int colAdjustment, Tile* tile);
  void fillTileBag(bool randomSeed);
};

#endif  // GAMEENGINE_H_
