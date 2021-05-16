#include "utils.h"

#include <sstream>
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

bool utils::checkData(int dataIndex, std::string data) {
    bool dataValid = false;
    if (dataIndex == 0 || dataIndex == 3 || dataIndex == 9) {
        dataValid = checkName(data);
    } else if (dataIndex == 1 || dataIndex == 4) {
        dataValid = checkValidNumber(data);
    } else if (dataIndex == 2 || dataIndex == 5 || dataIndex == 8) {
        dataValid = checkTiles(data);
    } else if (dataIndex == 6) {
        dataValid = checkBoardSize(data);
    } else if (dataIndex == 7) {
        dataValid = checkBoardDetails(data);
    }
    return dataValid;
}

bool utils::checkName(std::string name) {
    bool nameValid = true;
    if (name.length() == 0) {
        nameValid = false;
    }
    // Make sure all values are upper case (ASCII 65-90)
    for (size_t i = 0; i < name.length(); i++) {
        if (alphabet.find(name[i]) == std::string::npos) {
            nameValid = false;
        }
    }
    return nameValid;
}

bool utils::checkValidNumber(std::string score) {
    bool scoreValid = true;
    for (size_t i = 0; i < score.length() && scoreValid; ++i) {
        if (validNumbers.find(score[i]) == std::string::npos) {
            scoreValid = false;
        }
    }
    return scoreValid;
}

bool utils::checkTiles(std::string tiles) {
    bool tilesValid = true;
    std::istringstream tileData(tiles);
    std::string tile = "";
    while (std::getline(tileData, tile, ',') && tilesValid) {
        if (tile.length() == TILE_ATTRIBUTES) {
            tilesValid = checkTile(tile);
        } else {
            tilesValid = false;
        }
    }
    return tilesValid;
}

bool utils::checkBoardSize(std::string boardDimensions) {
    bool boardSizeValid = true;
    std::istringstream boardDimCheck(boardDimensions);
    std::string dimension = "";
    while (std::getline(boardDimCheck, dimension, ',') && boardSizeValid) {
        boardSizeValid = checkValidNumber(dimension);
        if (boardSizeValid) {
            int dimVal = std::stoi(dimension);
            if (dimVal > MAX_BOARD_DIMENSIONS || dimVal < 1) {
                boardSizeValid = false;
            }
        }
    }
    return boardSizeValid;
}

bool utils::checkBoardDetails(std::string boardInfo) {
    bool boardValid = true;
    std::istringstream boardTileCheck(boardInfo);
    std::string tileAndLoc = "";
    while (std::getline(boardTileCheck, tileAndLoc, ',')) {
        std::string data;
        std::istringstream tileLocSeparator(tileAndLoc);
        std::getline(tileLocSeparator, data, '@');
        boardValid = checkTile(data);
        std::getline(tileLocSeparator, data, '@');
        boardValid = checkCoordinate(data);
    }
    return boardValid;
}

bool utils::checkTile(std::string tile) {
    Colour colour = getColour(tile);
    Shape shape = getShape(tile);
    bool status = false;
    if (colour != '\0' && shape != 0) {
        status = true;
    }
    return status;
}

bool utils::checkCoordinate(std::string coord) {
    bool coordValid = false;
    if (coord.length() > 1 && coord.length() <= 3) {
        int row = parseRow(coord);
        int col = parseCol(coord);
        if (row >= 0 && row <= MAX_BOARD_DIMENSIONS && col >= 0 &&
                row <= MAX_BOARD_DIMENSIONS) {
            coordValid = true;
        }
    }
    return coordValid;
}

int utils::parseRow(std::string pos) {
    int row = -1;
    if (alphabet.find(pos[0]) != std::string::npos) {
        char rowVal = pos[0];
        row = static_cast<int>(rowVal - 65);
    }
    return row;
}

int utils::parseCol(std::string pos) {
    int col = -1;
    std::string colString = "";
    if (pos.length() == 2) {
        colString = pos.substr(1, 1);
    } else if (pos.length() == 3) {
        colString = pos.substr(1, 2);
    }
    if (checkValidNumber(colString)) {
        col = std::stoi(colString);
    }
    return col;
}