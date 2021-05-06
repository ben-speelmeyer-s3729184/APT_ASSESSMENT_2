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

        GameState* getGameState();
    void loadGameState(GameState* loadedState);

    std::string toString();
    void printBoard();

   private:
    bool initialTilePlaced;
    Player* player1;
    Player* player2;
    int noOfPlayers;
    LinkedList* tileBag;
    Board* board;
    void attemptTilePlacement(Player* player, int row, int col, Tile* tile);
    void topUpPlayerHand(Player* player);
    void updateScore(Player* player, Board* board, int col, int row, bool initialTilePlaced);
    bool checkForAdjacency(int row, int col);
    bool checkAdjacentTiles(int row, int rowAdjustment, int col, int colAdjustment, Tile* tile);
    void fillTileBag(bool randomSeed);
    void fillTileBag(std::string loadedTileBag);
};

#endif  // ASSIGN2_GAME_ENGINE_H