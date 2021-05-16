#ifndef UTILS_H
#define UTILS_H

#include "Definitions.h"
#include "Tile.h"
class utils {
public:
    /*
    * Gets the shape of a tile
    */
    Shape getShape(std::string tile);

    /*
    * Gets the colour of a tile
    */
    Colour getColour(std::string tile);

    /*
    * Performs various data integrity checks
    */
    bool checkData(int dataIndex, std::string data);

    /*
    * Function for checking player names
    */
    bool checkName(std::string name);

    /*
    * Checks that string is a valid integer
    */
    bool checkValidNumber(std::string score);

    /*
    * Checks validity of tile string
    */
    bool checkTiles(std::string tiles);

    /*
    * Validates string of board dimensions
    */
    bool checkBoardSize(std::string tiles);

    /*
    * Checks the save file representation of tiles
    */
    bool checkBoardDetails(std::string tiles);

    /*
    * Checks string representation of tile
    */
    bool checkTile(std::string tile);

    /*
    * Checks the string coordinate against board values
    */
    bool checkCoordinate(std::string coord);

    /*
    * Gets the integer value of a board row
    */
    int parseRow(std::string pos);

    /*
    * Gets the integer value of a board column
    */
    int parseCol(std::string pos);
};

#endif  // UTILS_H