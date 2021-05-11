#ifndef ASSIGN_BOARD_H
#define ASSIGN_BOARD_H

#include <string>
#include <vector>

#include "Tile.h"

#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

typedef std::vector<std::vector<Tile>> twoDVector;

class Board {
 public:
  Board();
  Board(std::string boardDetails);
  Board(const Board& other);

  ~Board();

  bool addTile(Tile* tile, int row, int col);

  Tile* getTile(int row, int col);

  // void printBoard();

  void resizeBoard(int row, int col);

  void setGridToNullPtr();

  std::string boardToString();

  // Matt's additions:
  bool checkTilePlacement(Tile* tile, int row, int col, bool initialTilePlaced);
  std::string boardDetails();
  std::string printBoard();
  int getRows();
  int getCols();

  const std::vector<std::vector<Tile*>>& getBoardVec() const { return boardVecs; }

 private:
  std::vector<std::vector<Tile*>> boardVecs;
  int rows;
  int cols;

  int asciiToInt(char letter);
  char intToAscii(int dec);

  // Matt Additions
  bool checkForAdjacency(int row, int col);
  bool checkAdjacentTiles(int row, int rowAdjustment, int col,
                          int colAdjustment, Tile* tile);
  int lineChecker(int row, int col, int rowAdjustment, int colAdjustment,
                  bool shapeMatch, bool colourMatch, Tile* tile);
};
#endif