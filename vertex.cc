#include "vertex.h"
#include "tile.h"
#include "edge.h"
#include "player.h"
#include <iostream>
using namespace std;

Vertex::Vertex(int idx): index{idx}, buildType{'-'}, owner{nullptr} {}
Vertex::~Vertex() {}

int Vertex::getIndex() { return index; }
char Vertex::getBuildType() { return buildType; }
int Vertex::getOwnerPos() { return ownerPos; }
Player* Vertex::getOwner() { return owner; }
vector<Edge*> Vertex::getNeighbourEdges() { return neighbourEdges; }

void Vertex::setIndex(int idx) { index = idx; }
void Vertex::setBuildType(char bt) { buildType = bt; }
void Vertex::setOwnerPos(int op) { ownerPos = op; }
void Vertex::setOwner( Player* ptrp ) { owner = ptrp; }

void Vertex::attachVertex( Vertex* ptrv ) {
    if ( ptrv == nullptr ) cout << "WARNING: NULLPTR parameter in Vertex::attachVertex!" << endl;
    neighbourVertices.emplace_back(ptrv);
}

void Vertex::attachEdge( Edge* ptre ) {
    if ( ptre == nullptr ) cout << "WARNING: NULLPTR parameter in Vertex::attachEdge!" << endl;
    neighbourEdges.emplace_back(ptre);
}

void Vertex::attachEdgeDoubly( Edge* ptre ) {
    if ( ptre == nullptr ) cout << "WARNING: NULLPTR parameter in Vertex::attachEdgeDoubly!" << endl;
    neighbourEdges.emplace_back(ptre);
    ptre->attachVertex(this);
}

void Vertex::wasNotified( Tile& whoNotified ) {
    if ( owner != nullptr ) {
        char tileResourceType = whoNotified.getResourceType();
        owner->addResource(tileResourceType);
    }
}
