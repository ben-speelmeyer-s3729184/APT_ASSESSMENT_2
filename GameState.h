#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

class GameState {
 private:
  /* data */
  Player* player1;
  Player* player2;
  LinkedList* tileBag;
  Board* board;

 public:
  GameState();
  GameState(Player* player1, Player* player2, LinkedList* tileBag,
            Board* board);
  ~GameState();

  Player* getPlayer1();
  Player* getPlayer2();
  Board* getBoard();
  LinkedList* getTileBag();
};

#endif