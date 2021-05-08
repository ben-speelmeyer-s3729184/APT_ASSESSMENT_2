#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <string>

class SaveLoad {
   private:
    std::string nameP1;
    std::string nameP2;
    int scoreP1;
    int scoreP2;

   public:
    SaveLoad();
    ~SaveLoad();

    void saveGame(std::string toSave);
    void loadGame();
};
#endif