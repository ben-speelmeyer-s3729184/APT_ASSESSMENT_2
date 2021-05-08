#include "TileFactory.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

TileFactory::TileFactory() {}

LinkedList* TileFactory::createTileBag(bool randomSeed) {
    LinkedList* tileBag = new LinkedList();
    int tileCount = 0;
    TilesImport tiles;
    importTileList(tiles);
    std::uniform_int_distribution<int> uniform_dist(0, MAX_TILE_BAG_SIZE - 1);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine randomNum(seed);
    std::default_random_engine randomNumStatic(0);

    //creates the random number generator with either a set seed or random seed.
    while (tileCount < MAX_TILE_BAG_SIZE) {
        int randIndex = 0;
        if (randomSeed) {
            randIndex = uniform_dist(randomNum);
        } else {
            randIndex = uniform_dist(randomNumStatic);
        }

        if (tiles[randIndex][COLOUR_IND] != '\0' && tiles[randIndex][SHAPE_IND] != '\0') {
            Colour colour = tiles[randIndex][COLOUR_IND];
            Shape shape = readShape(tiles[randIndex][SHAPE_IND]);
            Tile* tile = new Tile(colour, shape);
            tileBag->addTile(tile);
            ++tileCount;
            tiles[randIndex][COLOUR_IND] = '\0';
            tiles[randIndex][SHAPE_IND] = '\0';
        }
    }
    return tileBag;
}

LinkedList* TileFactory::createTileBag(std::string loadedTileBag) {
    LinkedList* tileBag = new LinkedList();
    std::string tileData;
    std::istringstream iss(loadedTileBag);

    while (std::getline(iss, tileData, ',')) {
        //std::cout << tileData << " " << tileData[0] << std::endl;
        Colour colour = tileData[COLOUR_IND];
        Shape shape = readShape(tileData[SHAPE_IND]);
        Tile* tile = new Tile(colour, shape);
        tileBag->addTile(tile);
    }
    return tileBag;
}


LinkedList* TileFactory::createHand(std::string hand, Player* player) {
    LinkedList* tbag = createTileBag(hand);

    int int_pos = 0;
    while(int_pos < tbag->size()){
        player->addTileToHand(tbag->takeFront());
        
    }
}

void TileFactory::importTileList(TilesImport tiles) {
    std::ifstream file("tileList.txt");
    int numRead = 0;
    while (!file.eof() && numRead < MAX_TILE_BAG_SIZE) {
        file >> tiles[numRead][COLOUR_IND];
        file >> tiles[numRead][SHAPE_IND];
        ++numRead;
    }
    file.close();
    
}

int TileFactory::readShape(char shape) {
    int shapeRet = '\0';
    if (shape == '1') {
        shapeRet = CIRCLE;
    } else if (shape == '2') {
        shapeRet = STAR_4;
    } else if (shape == '3') {
        shapeRet = DIAMOND;
    } else if (shape == '4') {
        shapeRet = SQUARE;
    } else if (shape == '5') {
        shapeRet = STAR_6;
    } else if (shape == '6') {
        shapeRet = CLOVER;
    }
    return shapeRet;
}

/*int TileFactory::readColor(char color) {
    int shapeRet = '\0';
    if (color == '1') {
        shapeRet = CIRCLE;
    } else if (color == '2') {
        shapeRet = STAR_4;
    } else if (color == '3') {
        shapeRet = DIAMOND;
    } else if (color == '4') {
        shapeRet = SQUARE;
    } else if (color == '5') {
        shapeRet = STAR_6;
    } else if (color == '6') {
        shapeRet = CLOVER;
    }
    return shapeRet;
}*/