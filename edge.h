#ifndef __EDGE_H__
#define __EDGE_H__
#include <iostream>
#include <vector>
#include "vertex.h"

class Vertex;

class Edge {
    int index;
    int ownerPos;
    std::vector<Vertex*> neighbourVertices;
    std::vector<Edge*> neighbourEdges;

    public:
    Edge(int idx = -1);
    ~Edge();
    int getIndex();
    int getOwnerPos();
    void setIndex(int idx);
    void setOwnerPos(int op);
    void attachVertex( Vertex* ptrv );
    void attachEdge( Edge* ptre );
};

#endif

