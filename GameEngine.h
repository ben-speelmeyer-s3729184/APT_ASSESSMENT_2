#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include "Board.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "TileFactory.h"
/**
 * Contain players, board and tileBag
 * additional variables: playerTurn?
 * controls tile distribution.
 * adds tiles to tilebag, or player hand depending on situation.
 * adds tiles to board if able to.
 * updates player score.
 */

class GameEngine {
   public:
    GameEngine(bool randomSeed);
    GameEngine(std::string fileName, bool fileLoaded);
    ~GameEngine();

    // Initialise the board, players, tileBags, and fill hands and tileBag with
    // tiles.

    bool playTile(int currentPlayer, int row, int col, Tile* tile);
    bool replaceTile(int currentPlayer, Tile* tile);

    bool addPlayer(std::string name);

    void updateGameState();

    GameState* retrieveGameState();
    std::string toString();
    void printBoard();

   private:
    bool initialTilePlaced;
    Player* player1;
    Player* player2;
    int noOfPlayers;
    GameState* gameState;
    LinkedList* tileBag;
    Board* board;

    void topUpPlayerHand(Player* player);
    void updateScore(Player* player, int row, int col);
    bool checkForAdjacency(int row, int col);
    bool checkLeftRightTiles(int row, int col, Tile* tile);
    bool checkUpDownTiles(int row, int col, Tile* tile);
    void fillTileBag(bool randomSeed);
    void fillTileBag(std::string loadedTileBag);
};

#endif  // ASSIGN2_GAME_ENGINE_H