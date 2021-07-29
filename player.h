#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include "vertex.h"
#include "edge.h"

class Player {
    int numHeat;
    int numWifi;
    int numEnergy;
    int numBrick;
    int numGlass;
    int numBuild;
    int buildPoints;
    std::vector<Vertex*> ownVertices;
    std::vector<Edge*> ownEdges;
    // Dice dice;

    public:
    Player();
    ~Player();
    int getNumResource(char resourceType);
    int getNumBuild();
    int getBuildPoint();
    
    void buildRes( Vertex* ptrv ); // WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
    void buildRoad( Edge* ptre ); 
    void improveRes( Vertex* ptrv );
    void addResource(char resourceType);
    void decResource(char resourceType);  // need to check non-0
    bool existResource();

    char beStolen();
    int rollDice( int value );
};

#endif

