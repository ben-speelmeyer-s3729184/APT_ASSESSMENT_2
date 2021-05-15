// Copyright 2021
#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "TileFactory.h"
#include "utils.h"

DataManager::DataManager() {}

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
      loadedData[i] = removeCarriageReturn(loadedData[i]);
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
    Board* board = recreateBoard(BOARD_DETAILS, BOARD_SIZE);

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

std::string DataManager::removeCarriageReturn(std::string fix) {
  if (fix[fix.length() - 1] == '\r') {
    fix.resize(fix.length() - 1);
  }
  return fix;
}
std::vector<std::string> DataManager::delimStringToVector(std::string deets,
                                                          std::string delim) {
  std::vector<std::string> details;
  std::string temp = "";
  std::string indexVal = "";
  for (size_t i = 0; i < deets.length(); i++) {
    indexVal = deets[i];
    // account for whitespace
    if ((indexVal == " " || indexVal == delim) && temp.length() > 0) {
      details.push_back(temp);
      temp = "";
      // if end of string, do final append
    } else if (i == deets.length() - 1) {
      if (indexVal != " " && indexVal != delim) {
        temp.append(indexVal);
      }
      details.push_back(temp);
    } else if (indexVal != " " && indexVal != delim) {
      temp.append(indexVal);
    }
  }

  return details;
}

std::vector<int> DataManager::getDimensions(std::string boardDimensions) {
  std::vector<std::string> strDims = delimStringToVector(boardDimensions, ",");
  std::vector<int> dims;
  dims.push_back(std::stoi(strDims[1]));
  dims.push_back(std::stoi(strDims[0]));
  return dims;
}

int DataManager::getTileLocationRow(std::string tileLoc) {
  // row can't exceed 'Z', so will be first position
  char val = tileLoc[0];
  return val - 65;
}

int DataManager::getTileLocationCol(std::string tileLoc) {
  int colVal = -1;
  std::string colString = "";
  std::string temp = "";
  if (tileLoc.length() > 1) {
    for (size_t i = 1; i < tileLoc.length(); i++) {
      temp = tileLoc[i];
      colString.append(temp);
    }
    colVal = std::stoi(colString);
  }
  return colVal;
}

void DataManager::loadTilePlacement(Board* board, std::string info) {
  // e.g. R1&
  // get tile
  std::vector<std::string> posVec = delimStringToVector(info, "@");
  utils util;
  Colour colr = util.getColour(posVec[0]);
  Shape shp = util.getShape(posVec[0]);
  Tile* tileToPlace = new Tile(colr, shp);

  int row = getTileLocationRow(posVec[1]);
  int col = getTileLocationCol(posVec[1]);
  // get position

  board->addTile(tileToPlace, row, col);
}

Board* DataManager::recreateBoard(std::string boardDetails,
                                  std::string boardDimensions) {
  // split string by commmas
  //    e.g. R1@D5,R5@G7 -> [R1@D5, R5@G7]
  //
  Board* board = new Board();
  std::vector<std::string> boardVec = delimStringToVector(boardDetails, ",");
  std::vector<int> dims = getDimensions(boardDimensions);

  int rows = dims[0];
  int cols = dims[1];

  board->resizeBoard(rows, cols);

  for (std::string cell : boardVec) {
    loadTilePlacement(board, cell);
  }
  return board;
}