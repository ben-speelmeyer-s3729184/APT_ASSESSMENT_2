#include "TileFactory.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>

TileFactory::TileFactory() {}

LinkedList* TileFactory::createTileBag() {
    LinkedList* tileBag = new LinkedList();
    int tileCount = 0;
    TilesImport tiles;
    importTileList(tiles);
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, MAX_TILE_BAG_SIZE - 1);

    while (tileCount < MAX_TILE_BAG_SIZE) {
        //implement random choice
        int randIndex = uniform_dist(randomSeed);
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
    return nullptr;
}

LinkedList* TileFactory::createHand(std::string hand) {
    return nullptr;
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