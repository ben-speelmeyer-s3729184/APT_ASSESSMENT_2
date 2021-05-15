// Copyright 2021
#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "TileFactory.h"

DataManager::DataManager() {}
std::string removeCarriageReturn(std::string fix);

bool DataManager::saveGame(GameState* saveGame, std::string fileName) {
  bool status = false;
  // Create and open a text file
  std::ofstream saveFile(fileName);

  // check status of stream
  if (saveFile) {
    // Write to the file
    saveFile << saveGame->toString();
    // Close File
    saveFile.close();
    status = true;
  }
  return status;
}

GameState* DataManager::loadGame(std::string fileName) {
  GameState* gameState = nullptr;

  std::ifstream loadFile(fileName);
  // check file was opened correctly
  if (loadFile) {
    // initialise temp variables
    std::string loadedData[NUMBER_OF_DATA_ENTRIES];
    for (int i = 0; i < NUMBER_OF_DATA_ENTRIES; ++i) {
      std::getline(loadFile, loadedData[i]);
      removeCarriageReturn(loadedData[i]);
    }

    // close file
    loadFile.close();

    // create tilebag
    int noOfPlayers = 0;
    Player* players[MAX_NUM_OF_PLAYERS];

    // player 1 details
    players[noOfPlayers] = new Player(PLAYER_1_NAME);
    players[noOfPlayers]->addScore(std::stoi(PLAYER_1_SCORE));
    TileFactory tileFactory;
    Hand* hand1 = tileFactory.createHand(PLAYER_1_HAND);

    while (hand1->size() > 0) {
      players[noOfPlayers]->addTileToHand(hand1->takeFront());
    }
    delete hand1;
    ++noOfPlayers;

    // player 2 details
    players[noOfPlayers] = new Player(PLAYER_2_HAND);
    players[noOfPlayers]->addScore(std::stoi(PLAYER_2_SCORE));

    Hand* hand2 = tileFactory.createHand(PLAYER_2_HAND);

    while (hand2->size() > 0) {
      players[noOfPlayers]->addTileToHand(hand2->takeFront());
    }

    ++noOfPlayers;
    delete hand2;
    // Recreate Board
    Board* board = new Board(BOARD_DETAILS, BOARD_SIZE);

    // initialise currentPlayerNumber to -1
    // to force an error if issue resuming players
    int currentPlayerNumber = -1;

    TileBag* tileBag = tileFactory.createTileBag(BOARD_SIZE);

    // Put data into GameState
    if (players[0]->getPlayerName() == CURRENT_PLAYER_NAME) {
      currentPlayerNumber = 0;
    } else {
      currentPlayerNumber = 1;
    }

    // delete gamestate object before re-assigning

    gameState = new GameState(players, tileBag, board, noOfPlayers,
                              currentPlayerNumber);
    delete tileBag;
    for (int i = 0; i < noOfPlayers; ++i) {
      delete players[i];
    }
    delete board;
  }

  return gameState;
}

std::string removeCarriageReturn(std::string fix) {
  if (fix[fix.length() - 1] == '\r') {
    fix.resize(fix.length() - 1);
  }
  return fix;
}