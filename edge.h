#ifndef __EDGE_H__
#define __EDGE_H__
#include <iostream>
#include <vector>
#include <memory>
#include "vertex.h"

class Player;
class Vertex;

class Edge {
    int index;
    int ownerPos;
    Player* owner;
    std::vector<Vertex*> neighbourVertices;
    //std::vector<shared_ptr<Edge>> neighbourEdges;

    public:
    Edge(int idx = -1);
    ~Edge();
    int getIndex();
    int getOwnerPos();
    Player* getOwner();
    std::vector<Vertex*> getNeighbourVertices();

    void setIndex(int idx);
    void setOwnerPos(int op);
    void setOwner(Player* ow);
    void attachVertex( Vertex* ptrv );
    //void attachEdge( Edge* ptre );
    //void attachVertexDoubly( Vertex* ptrv );
};

#endif

