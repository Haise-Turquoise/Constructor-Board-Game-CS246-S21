#include "edge.h"

Edge::Edge(int idx): index{idx}, ownerPos{-1} {}
Edge::~Edge() {}

int Edge::getIndex() { return index; }
int Edge::getOwnerPos() { return ownerPos; }

void Edge::setIndex(int idx) { index = idx; }
void Edge::setOwnerPos(int op) { ownerPos = op; }

void Vertex::attachVertex( Vertex* ptrv ) {
    neighbourVertices.emplace_back(ptrv);
}

void Vertex::attachEdge( Edge* ptre ) {
    neighbourEdges.emplace_back(ptre);
}