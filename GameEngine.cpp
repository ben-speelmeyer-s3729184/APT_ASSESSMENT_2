#include "GameEngine.h"
#include <fstream>
#include "utils.h"

GameEngine::GameEngine(bool randomSeed)
{
    noOfPlayers = 0;
    board = new Board();
    board->resizeBoard(25, 25);
    fillTileBag(randomSeed);
    initialTilePlaced = false;
    
}

GameEngine::GameEngine(std::string fileName, bool fileLoaded)
{
    //loadGame(fileName);
}

GameEngine::~GameEngine()
{
    delete player1;
    delete player2;
    delete tileBag;
    delete board;
}

// Initialise the board, players, tileBags, and fill hands and tileBag with
// tiles.
void GameEngine::fillTileBag(bool randomSeed)
{
    TileFactory tileFactory;
    tileBag = tileFactory.createTileBag(randomSeed);
}

void GameEngine::fillTileBag(std::string loadedTileBag)
{
    TileFactory tileFactory;
    tileBag = tileFactory.createTileBag(loadedTileBag);
}

bool GameEngine::playTile(int currentPlayer, int row, int col, Tile *tile)
{
    bool playedTile = false;
    Player *player = nullptr;
    if (currentPlayer == 1)
    {
        player = player1;
    }
    else if (currentPlayer == 2)
    {
        player = player2;
    }
    if (player != nullptr)
    {
        if (player->hasTile(tile))
        {
            if (board->getTile(row, col) == nullptr)
            {
                bool adjacentTiles = checkForAdjacency(row, col);
                if (initialTilePlaced && adjacentTiles)
                {
                    bool leftRightCheck = checkAdjacentTiles(row, 0, col, 1, tile);
                    bool upDownCheck = checkAdjacentTiles(row, 1, col, 0, tile);

                    if (leftRightCheck && upDownCheck)
                    {
                        attemptTilePlacement(player, row, col, tile);
                    }
                }
                else if (!initialTilePlaced)
                {
                    attemptTilePlacement(player, row, col, tile);
                    initialTilePlaced = true;
                }
            }
        }
    }
    topUpPlayerHand(player);
    return playedTile;
}

void GameEngine::attemptTilePlacement(Player *player, int row, int col, Tile *tile)
{
    Tile *tileFromHand = player->retrieveTile(tile);
    board->addTile(tileFromHand, row, col);
    updateScore(player, board, row, col, initialTilePlaced);
}

bool GameEngine::replaceTile(int currentPlayer, Tile *tile)
{
    Player *player = nullptr;
    bool tileExists = false;
    if (currentPlayer == 1)
    {
        player = player1;
    }
    else if (currentPlayer == 2)
    {
        player = player2;
    }
    if (player != nullptr)
    {
        tileExists = player->hasTile(tile);
        if (tileExists)
        {
            Tile *tileToReplace = player->retrieveTile(tile);
            tileBag->addTile(tileToReplace);
            player->addTileToHand(tileBag->takeFront());
        }
    }
    return tileExists;
}

bool GameEngine::addPlayer(std::string name, bool loading)
{
    bool playerAdded = false;
    if (noOfPlayers == 0)
    {
        player1 = new Player(name);
        if (!loading)
        {
            topUpPlayerHand(player1);
        }
        ++noOfPlayers;
        playerAdded = true;
    }
    else if (noOfPlayers == 1)
    {
        player2 = new Player(name);
        topUpPlayerHand(player2);
        ++noOfPlayers;
        playerAdded = true;
    }
    return playerAdded;
}

void GameEngine::updateScore(Player *player, Board *board, int row, int col, bool initialTilePlaced)
{
    utils utils;
    utils.updateScores(player, board, row, col, initialTilePlaced);
}

GameState *GameEngine::getGameState()
{
    GameState *gameState = new GameState(player1, player2, board, tileBag);
    return gameState;
}

void GameEngine::loadGameState(GameState *loadedState)
{
    Player *playerToDelete = player1;
    player1 = loadedState->getPlayer1();
    delete playerToDelete;
    playerToDelete = player2;
    player1 = loadedState->getPlayer1();
    delete playerToDelete;
    Board *boardToDelete = board;
    board = loadedState->getBoard();
    delete board;
    LinkedList *tileBagToDelete = tileBag;
    tileBag = loadedState->getTileBag();
    delete tileBagToDelete;
}

void GameEngine::topUpPlayerHand(Player *player)
{
    while (player->handSize() < HANDSIZE && tileBag->size() > 0)
    {
        Tile *tile = tileBag->takeFront();
        player->addTileToHand(tile);
    }
}

bool GameEngine::checkAdjacentTiles(int row, int rowAdjustment, int col, int colAdjustment, Tile *tile)
{
    bool validMove = false;
    Tile *prevTile = board->getTile(row - rowAdjustment, col - colAdjustment);
    Tile *postTile = board->getTile(row + rowAdjustment, col + colAdjustment);

    bool colourMatch = false;
    bool shapeMatch = false;

    //check whether tile to be added can be placed between
    //the positions above and below chosen position.
    utils utilities;
    utilities.adjacentTileChecker(validMove, colourMatch, shapeMatch, prevTile, postTile, tile);

    //If a tile can be placed next to the adjacent left and right tiles, checks if placing this tile will
    //create a line greater than 6 tiles in this position. If no, then a valid move is confirmed.
    if (validMove)
    {
        int adjacentTiles = 0;
        bool adjacentTile = true;
        int currentRow = row - rowAdjustment;
        int currentCol = col - colAdjustment;
        //Checks to left of chosen position first.
        while (adjacentTile && validMove)
        {
            Tile *tileCheck = board->getTile(currentRow, currentCol);
            if (tileCheck != nullptr)
            {
                if (colourMatch && tile->colour != tileCheck->colour)
                {
                    validMove = false;
                }
                else if (shapeMatch && tile->shape != tileCheck->shape)
                {
                    validMove = false;
                }
                else if (tileCheck == tile)
                {
                    validMove = false;
                }
                currentCol -= colAdjustment;
                currentRow -= rowAdjustment;
                ++adjacentTiles;
            }
            else
            {
                adjacentTile = false;
            }
        }
        //Checks right of chosen position.
        currentRow = row + rowAdjustment;
        currentCol = col + colAdjustment;
        adjacentTile = true;
        while (adjacentTile && validMove)
        {
            Tile *tileCheck = board->getTile(currentRow, currentCol);

            if (tileCheck != nullptr)
            {
                if (colourMatch && tile->colour != tileCheck->colour)
                {
                    validMove = false;
                }
                else if (shapeMatch && tile->shape != tileCheck->shape)
                {
                    validMove = false;
                }
                else if (tileCheck == tile)
                {
                    validMove = false;
                }
                currentCol += colAdjustment;
                currentRow += rowAdjustment;
                ++adjacentTiles;
            }
            else
            {
                adjacentTile = false;
            }
        }
        //Final check. If number of adjacent tiles in this column is more than 5
        //then tile cannot be placed.
        if (adjacentTiles > 5)
        {
            validMove = false;
        }
    }
    return validMove;
}

bool GameEngine::checkForAdjacency(int row, int col)
{
    bool tileAdjacent = false;
    if (board->getTile(row - 1, col) != nullptr || board->getTile(row + 1, col) != nullptr || board->getTile(row, col - 1) != nullptr || board->getTile(row, col + 1) != nullptr)
    {
        tileAdjacent = true;
    }
    return tileAdjacent;
}

void GameEngine::printBoard()
{
    board->printBoard();
}

std::string GameEngine::toString()
{
    std::string gameData;
    gameData.append(player1->getPlayerName() + "\n");
    gameData.append(std::to_string(player1->getPlayerScore()) + "\n");
    gameData.append(player1->getPlayerHand());
    gameData.append(player2->getPlayerName() + "\n");
    gameData.append(std::to_string(player2->getPlayerScore()) + "\n");
    gameData.append(player2->getPlayerHand());
    gameData.append(tileBag->toString());
    gameData.append(board->boardToString());
    return gameData;
}

void GameEngine::saveGame()
{
    // Create and open a text file
    std::ofstream saveFile("saveFiles/save2.txt");

    std::string saveData = toString();

    // Write to the file
    saveFile << saveData;
    //Close File
    saveFile.close();
};

void GameEngine::loadGame()
{
    std::ifstream loadFile("saveFiles/load1.txt");

    std::string name_player1;
    std::string score_player1;
    std::string player1Hand;
    std::string name_player2;
    std::string score_player2;
    std::string player2Hand;

    std::getline(loadFile, name_player1);
    std::getline(loadFile, score_player1);
    std::getline(loadFile, player1Hand);
    std::getline(loadFile, name_player2);
    std::getline(loadFile, score_player2);
    std::getline(loadFile, player2Hand);

    addPlayer(name_player1, true);
    this->player1->addScore(std::stoi(score_player1));

    TileFactory tileFactory;
    tileFactory.createHand(player1Hand, player1);
    
    //this->player1->addTileToHand()

    addPlayer(name_player2, true);
    this->player2->addScore(std::stoi(score_player2));
}

Tile GameEngine::tileGenerator(std::string data){
    
}

