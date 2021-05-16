// Copyright 2021
/**
 *
 * Player needs to be able to play a tile
 * Player has a hand
 * Player needs to add tiles to hand if handsize is <6.
 *
 * Potential Methods
 * Player has tile
 * PlayTile (retrieve tile from hand)
 * AddTileToHand()
 * HandSize()
 *
 * Define HandSize 6
 * GetHand - Return deep copy of hand.
 * PlayerDetails - Returns player details
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "Hand.h"

class Player {
public:
    /*
    * Constructor
    */
    Player(std::string playerName);


    /*
    * Copy constructor
    */
    Player(Player& player);

    /*
    * Destructor
    */
    ~Player();

    /*
    * Returns hand size
    */
    int handSize();

    /*
    * Checks if Player has a given tile
    */
    bool hasTile(Tile* tile);

    /*
    * Adds a tile to player hand
    */
    void addTileToHand(Tile* tile);

    /*
    * Pulls a tile from player hand
    */
    Tile* retrieveTile(Tile* tile);

    /*
    * Player name getter
    */
    std::string getPlayerName();

    /*
    * Prints a string representaion of player hand
    */
    std::string getPlayerHand();

    /*
    * Player score getter
    */
    int getPlayerScore();

    /*
    * Adds the scoreModifier to current player score
    */
    void addScore(int scoreModifier);

private:
    std::string* playerName;
    int playerScore;

    Hand* playerHand;
};

#endif  // PLAYER_H_
