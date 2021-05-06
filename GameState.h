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
    GameState(Player* player1, Player* player2, Board* board, LinkedList* tileBag);
    ~GameState();

    Player* getPlayer1();
    Player* getPlayer2();
    Board* getBoard();
    LinkedList* getTileBag();

    void initiatePlayer1(LinkedList* hand, std::string name, int score);
    void initiatePlayer2(LinkedList* hand, std::string name, int score);
    void initiateBoard(std::string boardInfo);
    void initiateTileBag(std::string tileBagInfo);
    void load(std::string fileName);
};

#endif