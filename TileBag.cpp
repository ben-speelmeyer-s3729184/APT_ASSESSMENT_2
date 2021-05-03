#include "TileBag.h"

TileBag::TileBag() { tileBag = new LinkedList(); }

TileBag::~TileBag() { delete tileBag; }

Tile* TileBag::drawTile() { return tileBag->takeFront(); }

void TileBag::returnTile(Tile* tile) { tileBag->addTile(tile); }

std::string TileBag::tileBagDetails() { return tileBag->toString(); }