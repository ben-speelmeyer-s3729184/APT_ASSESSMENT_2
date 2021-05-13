// Copyright 2021
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
#include <string>
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

#endif  // GAMESTATE_H_
