#include "utils.h"

Colour utils::getColour(std::string tile) {
  const char colChar = tile[0];
  Colour col = '\0';

  if (colChar == 'R') {
    col = RED;
  } else if (colChar == 'O') {
    col = ORANGE;
  } else if (colChar == 'Y') {
    col = YELLOW;
  } else if (colChar == 'G') {
    col = GREEN;
  } else if (colChar == 'B') {
    col = BLUE;
  } else if (colChar == 'P') {
    col = PURPLE;
  }
  return col;
}

Shape utils::getShape(std::string tile) {
  const char shpChar = tile[1];
  Shape shp = 0;
  if (shpChar == '1') {
    shp = CIRCLE;
  } else if (shpChar == '2') {
    shp = STAR_4;
  } else if (shpChar == '3') {
    shp = DIAMOND;
  } else if (shpChar == '4') {
    shp = SQUARE;
  } else if (shpChar == '5') {
    shp = STAR_6;
  } else if (shpChar == '6') {
    shp = CLOVER;
  }

  return shp;
}