#include "SaveLoad.h"

#include <fstream>

SaveLoad::SaveLoad() {
    this->nameP1 = "Sarthak";
    this->nameP2 = "Matt";
    this->scoreP1 = 10;
    this->scoreP2 = 20;
};

SaveLoad::~SaveLoad(){};

void SaveLoad::saveGame(std::string toSave) {
    // Create and open a text file
    std::ofstream saveFile("saveGames/save1.txt");

    // Write to the file
    saveFile << toSave;

    //Close File
    saveFile.close();
};

void SaveLoad::loadGame() {
    //Load file from path
    std::ifstream loadFile("load1.txt");

    std::string scoreP1_s;
    std::string scoreP2_s;

    //Read file, by line
    std::getline(loadFile, this->nameP1);
    std::getline(loadFile, this->nameP2);
    std::getline(loadFile, scoreP1_s);
    std::getline(loadFile, scoreP2_s);

    this->scoreP1 = std::stoi(scoreP1_s);
    this->scoreP2 = std::stoi(scoreP2_s);
}