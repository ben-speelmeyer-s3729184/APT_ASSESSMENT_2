#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H
#define MAX_NUM_OF_PLAYERS 2

#include "Board.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "TileFactory.h"

class GameEngine {
 public:
  GameEngine(bool randomSeed);
  ~GameEngine();

  // Game setup functions
  bool addPlayer(std::string name);
  GameState* getGameState();
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
  LinkedList* tileBag;
  Board* board;

  void placeTile(Player* player, int row, int col, Tile* tile);
  void topUpPlayerHand(Player* player);
  void updateScore(Player* player, int col, int row);
  bool checkForAdjacency(int row, int col);
  bool checkAdjacentTiles(int row, int rowAdjustment, int col,
                          int colAdjustment, Tile* tile);
  void fillTileBag(bool randomSeed);
};

#endif  // ASSIGN2_GAME_ENGINE_H