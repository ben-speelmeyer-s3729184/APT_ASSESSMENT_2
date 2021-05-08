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
  Player** players;
  LinkedList* tileBag;
  Board* board;

 public:
  GameState();
  GameState(Player** players, LinkedList* tileBag, Board* board);
  ~GameState();

  Player** getPlayers();
  Board* getBoard();
  LinkedList* getTileBag();
};

#endif