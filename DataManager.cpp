#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "TileFactory.h"

bool DataManager::saveGame(GameState* saveGame) {
  // Create and open a text file
  std::ofstream saveFile("saveFiles/save2.txt");
  std::string gameData;
  for (int i = 0; i < saveGame->getNoOfPlayers(); ++i) {
    Player* player = saveGame->getPlayers()[i];
    gameData.append(player->getPlayerName() + "\n");
    gameData.append(std::to_string(player->getPlayerScore()) + "\n");
    gameData.append(player->getPlayerHand());
  }
  gameData.append(saveGame->getTileBag()->toString());
  gameData.append(saveGame->getBoard()->boardToString());
  // Write to the file
  saveFile << gameData;
  // Close File
  saveFile.close();
};

GameState* DataManager::loadGame(std::string fileName) {
  std::ifstream loadFile("saveFiles/load1.txt");

  std::string name_player1;
  std::string score_player1;
  std::string player1Hand;
  std::string name_player2;
  std::string score_player2;
  std::string player2Hand;
  std::string tileBag;
  std::string boardSize;
  std::string boardDetails;

  std::getline(loadFile, name_player1);
  std::getline(loadFile, score_player1);
  std::getline(loadFile, player1Hand);
  std::getline(loadFile, name_player2);
  std::getline(loadFile, score_player2);
  std::getline(loadFile, player2Hand);
  std::getline(loadFile, tileBag);
  std::getline(loadFile, boardSize);
  std::getline(loadFile, boardDetails);

  TileFactory tileFactory;
  LinkedList* tileBag = tileFactory.createTileBag(tileBag);
  int noOfPlayers = 0;
  Player* players[MAX_NUM_OF_PLAYERS];
  players[noOfPlayers] = new Player(name_player1);
  players[noOfPlayers]->addScore(std::stoi(score_player1));
  LinkedList* hand = tileFactory.createHand(player1Hand);
  while (hand->size() > 0) {
    players[noOfPlayers]->addTileToHand(hand->takeFront());
  }
  ++noOfPlayers;

  players[noOfPlayers] = new Player(name_player2);
  players[noOfPlayers]->addScore(std::stoi(score_player2));
  LinkedList* hand = tileFactory.createHand(player1Hand);
  while (hand->size() > 0) {
    players[noOfPlayers]->addTileToHand(hand->takeFront());
  }
  ++noOfPlayers;

  // Recreate Board

  GameState* loadGame = new GameState();
  return loadGame;
}