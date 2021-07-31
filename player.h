#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include "vertex.h"
#include "edge.h"
#include "dice.h"
#include "strategy.h"

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
    std::vector<char> generateResBoard(); //刘书辰的helper

    public:
    Player();
    ~Player();
    int getNumResource(char resourceType);
    int getNumBuild();
    int getBuildPoint();
    
    bool buildResFree( Vertex* ptrv );
    bool buildRes( Vertex* ptrv ); // WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
    bool buildRoad( Edge* ptre ); 
    bool improveRes( Vertex* ptrv );
    void addResource(char resourceType);
    bool decResource(char resourceType);  // need to check non-0
    bool existResource();

    char beStolen(int seed);
    int rollDice( int value , bool randDice, int seed); // if roll random dice -> randDice set to true, otherwise set to false
    void loseHalfResource(int seed);
};

#endif

