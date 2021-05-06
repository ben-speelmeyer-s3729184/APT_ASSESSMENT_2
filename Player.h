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

#ifndef ASSIGN1_PLAYER_H
#define ASSIGN1_PLAYER_H

#define HANDSIZE 6

class Player {
   public:
    Player(std::string playerName);
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
    std::string playerName;
    int playerScore;
    //Hand* playerHand;
    LinkedList* playerHand;
};

#endif  // ASSIGN1_PLAYER_H