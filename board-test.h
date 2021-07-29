#include "subject.h"
#include "observer.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include <vector>
#include <string>

class Board {
    std::vector<Tile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    public:
    // ctor
    Board();
    void clearBoard();
    void printBoard();
    void printAllPlayerStatus();
    void printCurPlayerStatus();

    void initAttachBoard();
    void initRandBoard();
    void initLoadBoard( std::string file );
    void initSeedBoard( int seed );
    void loadGame( std::string file );
    std::string saveGame();

    void buildRes( int pos );
    void buildRoad( int pos );
    void improveRes( int pos );

    void trade( char otherplayer, char ownResources, char otherResource );
    void moveGeese( int pos );
    void endCurTurn();




    
    


};