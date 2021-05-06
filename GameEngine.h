#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include "Board.h"
#include "GameState.h"
#include "Player.h"
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
    GameEngine(std::string player1Name, std::string player2Nam);
    ~GameEngine();

    // Initialise the board, players, tileBags, and fill hands and tileBag with
    // tiles.
    void initialiseGame();

    bool playTile(int currentPlayer, int row, int col, Tile* tile);
    bool replaceTile(int currentPlayer, Tile* tile);

    void updateGameState();
    GameState* retrieveGameState();

   private:
    Player* player1;
    Player* player2;
    GameState* gameState;
    LinkedList* tileBag;
    Board* board;
    void topUpPlayerHand(Player* player);
    void updateScore(Player* player, int col, int row);

    bool checkLeftRightTiles(int row, int col, Tile* tile);
    bool checkUpDownTiles(int row, int col, Tile* tile);
};

#endif  // ASSIGN2_GAME_ENGINE_H