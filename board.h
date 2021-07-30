#include "subject.h"
#include "observer.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "player.h"
#include <vector>
#include <string>
#include <queue>

class Board {
    int posGeese = 7 ;
    int seed = 0;
    std::vector<Tile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    //std::vector<Player*> players;
    //std::queue<char> playerQueue;
    int curTurn = 0;

    public:
    // ctor
    Board();
    int getCurTurn() const;
    void setCurTurn(int ind);

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

    void rollDice(bool fair);

    void buildRes( int pos );
    void buildRoad( int pos );
    void improveRes( int pos );

    void trade( std::string otherplayer, std::string ownResources, std::string otherResource );
    void moveGeese( int pos );

    bool checkWon();

    void endCurTurn();
    
    


};
