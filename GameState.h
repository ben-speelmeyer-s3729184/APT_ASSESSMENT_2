#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "LinkedList.h"

class GameState
{
private:
    /* data */
    std::string player1;
    std::string player2;
    LinkedList player1Hand;
    LinkedList player2Hand;
public:
    GameState(/* args */);
    ~GameState();


    void load(std::string fileName);

};


#endif