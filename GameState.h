#ifndef GAMESTATE_H
#define GAMESTATE_H
#define MAX_NUM_OF_PLAYERS 2

#include <iostream>

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

class GameState {
 private:
  /* data */
  Player* players[MAX_NUM_OF_PLAYERS];
  LinkedList* tileBag;
  Board* board;
  int noOfPlayers;

 public:
  GameState();
  GameState(Player** players, LinkedList* tileBag, Board* board,
            int noOfPlayers);
  GameState(const GameState& other);
  ~GameState();

  Player** getPlayers();
  Board* getBoard();
  LinkedList* getTileBag();
  int getNoOfPlayers() { return noOfPlayers; }
  std::string toString();
  int currentPlayer;
};

#endif