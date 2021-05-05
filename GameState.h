#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "LinkedList.h"
#include <iostream>

class GameState
{
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