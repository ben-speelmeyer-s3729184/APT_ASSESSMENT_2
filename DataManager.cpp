#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "TileFactory.h"

DataManager::DataManager(){};

bool DataManager::saveGame(GameState* saveGame, std::string fileName) {
  bool status = false;
  // Create and open a text file
  std::ofstream saveFile;
  saveFile.open(fileName);
  // check status of stream
  if (saveFile.good()) {
    // Write to the file
    saveFile << saveGame->toString();
    // Close File
    saveFile.close();
    status = true;
  }
  return status;
}

GameState* DataManager::loadGame(std::string fileName) {
  std::ifstream loadFile("saveFiles/load1.txt");

  std::string name_player1;
  std::string score_player1;
  std::string player1Hand;
  std::string name_player2;
  std::string score_player2;
  std::string player2Hand;
  std::string boardSize;
  std::string boardDetails;
  std::string loadedTileBag;
  std::string currPlayerName;

  std::getline(loadFile, name_player1);
  std::getline(loadFile, score_player1);
  std::getline(loadFile, player1Hand);
  std::getline(loadFile, name_player2);
  std::getline(loadFile, score_player2);
  std::getline(loadFile, player2Hand);
  std::getline(loadFile, boardSize);
  std::getline(loadFile, boardDetails);
  std::getline(loadFile, loadedTileBag);
  std::getline(loadFile, currPlayerName);

  loadFile.close();

  TileFactory tileFactory;
  LinkedList* tileBag = tileFactory.createTileBag(loadedTileBag);
  int noOfPlayers = 0;
  Player* players[MAX_NUM_OF_PLAYERS];
  players[noOfPlayers] = new Player(name_player1);
  players[noOfPlayers]->addScore(std::stoi(score_player1));
  LinkedList* hand1 = tileFactory.createHand(player1Hand);
  while (hand1->size() > 0) {
    players[noOfPlayers]->addTileToHand(hand1->takeFront());
  }
  ++noOfPlayers;

  players[noOfPlayers] = new Player(name_player2);
  players[noOfPlayers]->addScore(std::stoi(score_player2));
  LinkedList* hand2 = tileFactory.createHand(player1Hand);
  while (hand2->size() > 0) {
    players[noOfPlayers]->addTileToHand(hand2->takeFront());
  }
  ++noOfPlayers;

  // Recreate Board
  Board* board = new Board(boardDetails, boardSize);

  // // TODO: Sort out current player for load
  int currentPlayerNumber = -1;
  // Put data into GameState
  if (players[0]->getPlayerName() == currPlayerName) {
    currentPlayerNumber = 0;
  } else {
    currentPlayerNumber = 1;
  }

  GameState* loadedGame =
      new GameState(players, tileBag, board, noOfPlayers, currentPlayerNumber);
  return loadedGame;
}