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
    //int rollDice( int value , bool randDice, int seed); // if roll random dice -> randDice set to true, otherwise set to false
    void loseHalfResource(int seed);
};

#endif


/*

                          | 0|-- 0--| 1|
                            |         |
                            1    0    2
                            |  BRICK  |
                | 2|-- 3--| 3|   4  | 4|-- 4--| 5|
                  |         |         |         |
                  5    1    6         7    2    8
                  |  HEAT   |         |  HEAT   |
      | 6|-- 9--| 7|   6  | 8|--10--| 9|   5  |10|--11--|11|
        |         |         |         |         |         |
       12    3   13        14    4   15        16    5   17
        |  GLASS  |         | ENERGY  |         |  WIFI   |
      |12|   8  |13|--18--|14|  11  |15|--19--|16|  12  |17|
        |         |         |         |         |         |
       20        21    6   22        23    7   24        25
        |         | ENERGY  |         |  PARK   |         |
      |18|--26--|19|   9  |20|--27--|21|      |22|--28--|23|
        |         |         |         |         |         |
       29    8   30        31    9   32        33   10   34
        |  HEAT   |         |  GLASS  |         |  BRICK  |
      |24|   2  |25|--35--|26|   3  |27|--36--|28|  10  |29|
        |         |         |         |         |         |
       37        38   11   39        40   12   41        42
        |         |  WIFI   |         | ENERGY  |         |
      |30|--43--|31|   4  |32|--44--|33|  11  |34|--45--|35|
        |         |         |         |         |         |
       46   13   47        48   14   49        50   15   51
        |  WIFI   |         |  GLASS  |         |  BRICK  |
      |36|   8  |37|--52--|38|   5  |39|--53--|40|   9  |41|
        |         |         |         |         |         |
       54        55   16   56        57   17   58        59
        |         | ENERGY  |         |  BRICK  |         |
      |42|--60--|43|  10  |44|--61--|45|   6  |46|--62--|47|
                  |         |         |         |
                 63        64   18   65        66
                  |         |  GLASS  |         |
                |48|--67--|49|   3  |50|--68--|51|
                            |         |
                           69        70
                            |         |
                          |52|--71--|53|
*/
