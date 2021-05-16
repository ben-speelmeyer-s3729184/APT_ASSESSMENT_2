// Copyright 2021
#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <vector>

#include "Definitions.h"
#include "Tile.h"

typedef std::vector<std::vector<Tile>> twoDVector;

class Board {
public:
    /*
    * Default constructor
    */
    Board();

    /*
    * Copy constructor
    */
    Board(Board& other);

    /*
    * Destructor
    */
    ~Board();

    /*
    * Adds a tile to the board at position (row, col).
    * Returns false if board position is not null.
    * This function performs no error for bounds, it is assumed
    * that the callee will do so before calling.
    */
    bool addTile(Tile* tile, int row, int col);

    /*
    * Returns a pointer to a tile at given position.
    * This function performs no error for bounds, it is assumed
    * that the callee will do so before calling.
    */
    Tile* getTile(int row, int col);

    /*
    * Changes the size of the board to row x col and resets
    * row/col data members.
    */
    void resizeBoard(int row, int col);

    /*
    * TODO implement or delete
    */
    void setGridToNullPtr();

    /*
    * Returns string representation of board for saving.
    */
    std::string boardToString();

    /*
    * Checks if tile can be legally put into the given row/col position.
    * Returns true if tile can be placed.
    */
    bool checkTilePlacement(Tile* tile, int row,
                            int col, bool initialTilePlaced);


    /*
    * TODO:: Implement or delete!
    */
    std::string boardDetails();

    /*
    * Returns string representation of board. Intended
    * for use with Cli.
    */
    std::string printBoard();

    /*
    * Row getter.
    */
    int getRows();

    /*
    * Col getter.
    */
    int getCols();

    const std::vector<std::vector<Tile*>>& getBoardVec() const {
      return boardVecs;
    }

private:
    std::vector<std::vector<Tile*>> boardVecs;
    int rows;
    int cols;

    /*
    * Returns integer equivalent of upper-case ASCII letter
    */
    int asciiToInt(char letter);

    /*
    * Returns ASCII-encoded character of given int
    */
    char intToAscii(int dec);

    /*
    * Checks if a board position has any adjacent tiles
    */
    bool checkForAdjacency(int row, int col);


    /*
    * Checks tiles adjacent to tile placement location for valid move
    */
    bool checkAdjacentTiles(int row, int rowAdjustment, int col,
                            int colAdjustment, Tile* tile);

    /*
    * Returns number of tiles within row
    */
    int lineChecker(int row, int col, int rowAdjustment, int colAdjustment,
                    bool shapeMatch, bool colourMatch, Tile* tile);
};
#endif  // BOARD_H_
