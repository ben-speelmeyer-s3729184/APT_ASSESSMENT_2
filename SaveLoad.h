#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <string>
#include "Hand.h"

class SaveLoad{
    private:
    std::string nameP1;
    std::string nameP2;
    Hand handP1;
    Hand handP2;
    int scoreP1;
    int scoreP2;

    public:
    SaveLoad();
    ~SaveLoad();
    
    void saveGame();
    void loadGame();
    
};
#endif