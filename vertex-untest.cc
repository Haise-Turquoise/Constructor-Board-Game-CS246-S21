#include "vertex.h"
#include "tile.h"

Vertex::Vertex(int idx): index{idx}, buildType{'-'}, owner{nullptr} {}
Vertex::~Vertex() {}

int Vertex::getIndex() { return index; }
char Vertex::getBuildType() { return buildType; }
int Vertex::getOwnerPos() { return ownerPos; }
Player* Vertex::getOwner() { return owner; }

void Vertex::setIndex(int idx) { index = idx; }
void Vertex::setBuildType(char bt) { buildType = bt; }
void Vertex::setOwnerPos(int op) { ownerPos = op; }
void Vertex::setOwner( Player* ptrp ) { owner = ptrp; }

void Vertex::attachVertex( Vertex* ptrv ) {
    neighbourVertices.emplace_back(ptrv);
}

void Vertex::attachEdge( Edge* ptre ) {
    neighbourEdges.emplace_back(ptre);
}

void Vertex::wasNotified( Tile& whoNotified ) {
    if ( owner != nullptr ) {
        // char tileResourceType = whoNotified.getResourceType();
        // owner->addResources(tileResourceType);
    }
}