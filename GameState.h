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
    // ============= data members =============
    Player* players[MAX_NUM_OF_PLAYERS];
    TileBag* tileBag;
    Board* board;
    int noOfPlayers;
    int currentPlayer;

public:
    /*
    * Default constructor
    */
    GameState();

    /*
    * Creates GameState object with all members initialised
    */
    GameState(Player** players, TileBag* tileBag, Board* board, int noOfPlayers,
              int currentPlayer);

    /*
    * Copy constructor
    */
    GameState(const GameState& other);

    /*
    * Destructor
    */
    ~GameState();

    /*
    * Gets players member variable
    */
    Player** getPlayers();

    /*
    * Gets board member variable
    */
    Board* getBoard();

    /*
    * Gets tilebag member variable
    */
    TileBag* getTileBag();

    /*
    * Gets the current player (0 = player 1, 1 = player 2)
    */
    int getCurrentPlayer();

    /*
    * Gets number of players
    */
    int getNoOfPlayers() { return noOfPlayers; }

    /*
    * Returns a complete string representation of
    * the gamestate of saving purposes.
    */
    std::string toString();
};

#endif  // GAMESTATE_H_
