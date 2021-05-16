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
    /*
    * Constructor, will randomly fill tilebag if
    * randomSeed is true.
    */
    GameEngine(bool randomSeed);

    /*
    * Destructor
    */
    ~GameEngine();

    // ============= Game setup functions =============

    /*
    * Adds a player to engine. No error checking
    * is performed, this is responsibility of caller.
    */
    bool addPlayer(std::string name);

    /*
    * Generates a gamestate based on the state
    * of GameEngine instance.
    */
    GameState* getGameState(int currentPlayer);

    /*
    * Clears current game state and loads a previously saved game.
    */
    void loadGameState(GameState* loadedState);

    // ============= Tile placement functions =============

    /*
    * Checks that a tile played by a given player can legally be played
    */
    bool checkTilePlacement(Player* player, int row, int col, Tile* tile);

    /*
    * Replaces given tile in player hand
    */
    bool replaceTile(Player* player, Tile* tile);

    /*
    * TODO: implement or delete!
    */
    bool checkTilePlaceability(int row, int col, Tile* tile);

    /*
    * Perform end of round routines, place tile, calculate score,
    * top up hand and check win conditions.
    */
    bool endOfRoundCalculations(Player* player, int row, int col, Tile* tile);

    Player* getPlayer(int playerNumber);
    int getNoOfPlayers();

    /*
    * Returns the board details via Board's printBoard() method
    */
    std::string printBoard();

    /*
    * Returns an ordered vector with board dimensions (row, col)
    */
    std::vector<int> getBoardSize();

private:
    bool initialTilePlaced;
    Player** players;
    int noOfPlayers;
    int currPlayer = 0;
    TileBag* tileBag;
    Board* board;

    /*
    * Utility function called by destructor
    */
    void clear();

    /*
    * Places tile on board and removes from player hand
    */
    void placeTile(Player* player, int row, int col, Tile* tile);

    /*
    * Adds tile from tilebag to player's hand
    */
    void topUpPlayerHand(Player* player);

    /*
    * Increases player's score using ScoreManager
    */
    void updateScore(Player* player, int col, int row);

    /*
    * Checks board if any tiles are adjacent to row, col position
    * Returns true if adjacent tile exists.
    */
    bool checkForAdjacency(int row, int col);

    /*
    * Checks if given tile can legally be placed in proposed
    * position. Returns true if tile can be placed.
    */
    bool checkAdjacentTiles(int row, int rowAdjustment, int col,
                          int colAdjustment, Tile* tile);

    /*
    * Fills tilebag with tiles, will do so randomly if
    * randomSeed is set to true
    */
    void fillTileBag(bool randomSeed);
};

#endif  // GAMEENGINE_H_
