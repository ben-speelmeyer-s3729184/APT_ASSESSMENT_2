#ifndef UTILS_H
#define UTILS_H

#include "Definitions.h"
#include "Tile.h"
class utils {
 public:
  Shape getShape(std::string tile);
  Colour getColour(std::string tile);

  bool checkData(int dataIndex, std::string data);
  bool checkName(std::string name);
  bool checkValidNumber(std::string score);
  bool checkTiles(std::string tiles);
  bool checkBoardSize(std::string tiles);
  bool checkBoardDetails(std::string tiles);
  bool checkTile(std::string tile);
  bool checkCoordinate(std::string coord);

  int parseRow(std::string pos);
  int parseCol(std::string pos);
};

#endif  // UTILS_H