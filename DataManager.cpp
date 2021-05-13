// Copyright 2021
#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "TileFactory.h"

DataManager::DataManager() {}

bool DataManager::saveGame(GameState& saveGame, std::string fileName) {
  bool status = false;
  // Create and open a text file
  std::ofstream saveFile(fileName);

  // check status of stream
  if (saveFile) {
    // Write to the file
    saveFile << saveGame.toString();
    // Close File
    saveFile.close();
    status = true;
  }
  return status;
}

bool DataManager::loadGame(GameState& gameState, std::string fileName) {

  bool status = false;

  std::ifstream loadFile(fileName);

  // check file was opened correctly
  if (loadFile) {
    // initialise temp variables
    std::string name_player1 = "";
    std::string score_player1 = "";
    std::string player1Hand = "";
    std::string name_player2 = "";
    std::string score_player2 = "";
    std::string player2Hand = "";
    std::string boardSize = "";
    std::string boardDetails = "";
    std::string loadedTileBag = "";
    std::string currPlayerName = "";

    // read variables from file
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

    // close file
    loadFile.close();

    // create tilebag
    TileFactory tileFactory;
    LinkedList* tileBag = tileFactory.createTileBag(loadedTileBag);

    int noOfPlayers = 0;
    Player* players[MAX_NUM_OF_PLAYERS];

    // player 1 details
    players[noOfPlayers] = new Player(name_player1);
    players[noOfPlayers]->addScore(std::stoi(score_player1));

    LinkedList* hand1 = tileFactory.createHand(player1Hand);

    while (hand1->size() > 0) {
      players[noOfPlayers]->addTileToHand(hand1->takeFront());
    }

    ++noOfPlayers;

    // player 2 details
    players[noOfPlayers] = new Player(name_player2);
    players[noOfPlayers]->addScore(std::stoi(score_player2));

    LinkedList* hand2 = tileFactory.createHand(player1Hand);

    while (hand2->size() > 0) {
      players[noOfPlayers]->addTileToHand(hand2->takeFront());
    }

    ++noOfPlayers;

    // Recreate Board
    Board* board = new Board(boardDetails, boardSize);

    // initialise currentPlayerNumber to -1
    // to force an error if issue resuming players
    int currentPlayerNumber = -1;

    // Put data into GameState
    if (players[0]->getPlayerName() == currPlayerName) {
      currentPlayerNumber = 0;
    } else {
      currentPlayerNumber = 1;
    }

    // delete gamestate object before re-assigning

    gameState = GameState(players, tileBag, board, noOfPlayers, currentPlayerNumber);

    status = true;
  }

  return status;

}
