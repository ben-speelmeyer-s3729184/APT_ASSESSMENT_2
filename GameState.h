#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>

#include "LinkedList.h"

class GameState {
   private:
    /* data */
    std::string player1;
    std::string player2;
    LinkedList player1Hand;
    LinkedList player2Hand;

   public:
    GameState();
    ~GameState();

    void load(std::string fileName);
};

#endif