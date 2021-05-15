#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

// General Definitions
#define PLAYER_1 0
#define PLAYER_2 1
#define MAX_BOARD_DIMENSIONS 26

// Board Details
#define EMPTY_SPACE "  "
#define WALL "|"
#define HEADER "__"

// Player Details
#define MAX_NUM_OF_PLAYERS 2
#define HANDSIZE 6

// Scoring
#define QWIRKLE 6
#define MAX_TILES_LINE 6

#define MAX_TILE_BAG_SIZE 72
#define TILE_ATTRIBUTES 2

// Tile details
#define COLOUR_IND 0
#define SHAPE_IND 1

// Consts
const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string validNumbers = "0123456789";
#endif  // DEFINITIONS_H