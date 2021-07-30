#include "tile.h"
#include "observer.h"

Tile::Tile(int idx): index{idx}, resourceType{'-'}, value{-1} {}
Tile::~Tile() {}

int Tile::getIndex() { return index; }
char Tile::getResourceType() { return resourceType; }
int Tile::getValue() { return value; }

void Tile::setIndex(int idx) { index = idx; }
void Tile::setResourceType(char rt) { resourceType = rt; }
void Tile::setValue(int v) { value = v; }

void Tile::notifyObservers() {
    for ( size_t i = 0; i < observers.size(); i++ ) {
        observers[i]->wasNotified(*this);
    }
}
