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

#define HANDSIZE 6
#include <string>

#include "LinkedList.h"

class Player {
 public:
  Player(std::string playerName);  // Single-parameter constructors should be
                                   // marked explicit.  [runtime/explicit] [5]
  Player(Player& player);
  ~Player();

  int handSize();
  bool hasTile(Tile* tile);
  void addTileToHand(Tile* tile);
  Tile* retrieveTile(Tile* tile);

  std::string getPlayerName();
  std::string getPlayerHand();
  int getPlayerScore();
  void addScore(int scoreModifier);

 private:
  std::string* playerName;
  int playerScore;
  // Hand* playerHand;
  LinkedList* playerHand;
};

#endif  // PLAYER_H_
