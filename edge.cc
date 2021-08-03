#include "edge.h"
#include "vertex.h"
#include "player.h"
#include <iostream>
#include <memory>
using namespace std;

Edge::Edge(int idx): index{idx}, ownerPos{-1}, owner{nullptr} {}
Edge::~Edge() {}

int Edge::getIndex() { return index; }
int Edge::getOwnerPos() { return ownerPos; }
Player* Edge::getOwner() { return owner; }
vector<Vertex*> Edge::getNeighbourVertices() { return neighbourVertices; }


void Edge::setIndex(int idx) { index = idx; }
void Edge::setOwnerPos(int op) { ownerPos = op; }
void Edge::setOwner(Player* ow) { owner = ow; }

void Edge::attachVertex( Vertex* ptrv ) {
    if ( ptrv == nullptr ) cout << "WARNING: NULLPTR parameter in Edge::attachVertex!" << endl;
    neighbourVertices.emplace_back(ptrv);
}

/*
void Edge::attachEdge( Edge* ptre ) {
    if ( ptre == nullptr ) cout << "WARNING: NULLPTR parameter in Edge::attachEdge!" << endl;
    neighbourEdges.emplace_back(ptre);
}

void Edge::attachVertexDoubly( Vertex* ptrv ) {
    if ( ptrv == nullptr ) cout << "WARNING: NULLPTR parameter in Edge::attachVertexDoubly!" << endl;
    neighbourVertices.emplace_back(ptrv);
    ptrv->attachEdge(this);
}
*/