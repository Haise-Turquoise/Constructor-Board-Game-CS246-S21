#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <vector>
#include "observer.h"

class Player;
class Tile;
class Edge;

class Vertex : public Observer {
    int index;
    char buildType;
    int ownerPos; // position of owner in the players vector in Board (0-3)
    Player* owner;
    std::vector<Vertex*> neighbourVertices;
    std::vector<Edge*> neighbourEdges;

    public:
    Vertex(int idx = -1);
    ~Vertex();
    int getIndex();
    char getBuildType();
    int getOwnerPos();
    Player* getOwner();
    void setIndex(int idx);
    void setBuildType(char bt);
    void setOwnerPos(int op);
    void setOwner( Player* ptrp );
    void attachVertex( Vertex* ptrv );
    void attachEdge( Edge* ptre );
    void attachEdgeDoubly( Edge* ptre );


    virtual void wasNotified( Tile& whoNotified ) override;
};

#endif

