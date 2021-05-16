#include "TileBag.h"

TileBag::TileBag() { tileBag = new LinkedList(); }
TileBag::TileBag(TileBag& tileBag) {
    this->tileBag = new LinkedList(*tileBag.tileBag);
}
TileBag::~TileBag() { delete tileBag; }

void TileBag::addTile(Tile* tile) { tileBag->addTile(tile); }
Tile* TileBag::takeFront() { return tileBag->takeFront(); }
int TileBag::size() { return tileBag->size(); }
std::string TileBag::toString() { return tileBag->toString(); }