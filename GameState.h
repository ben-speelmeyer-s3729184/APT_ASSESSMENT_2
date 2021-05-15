// Copyright 2021
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
#include <string>

#include "Board.h"
#include "Definitions.h"
#include "Player.h"
#include "TileBag.h"
class GameState {
 private:
  /* data */
  Player* players[MAX_NUM_OF_PLAYERS];
  TileBag* tileBag;
  Board* board;
  int noOfPlayers;
  int currentPlayer;

 public:
  GameState();
  GameState(Player** players, TileBag* tileBag, Board* board, int noOfPlayers,
            int currentPlayer);
  GameState(const GameState& other);
  ~GameState();

  Player** getPlayers();
  Board* getBoard();
  TileBag* getTileBag();
  int getCurrentPlayer();
  int getNoOfPlayers() { return noOfPlayers; }
  std::string toString();
};

#endif  // GAMESTATE_H_
