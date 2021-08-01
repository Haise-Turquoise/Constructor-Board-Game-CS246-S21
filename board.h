#include "subject.h"
#include "observer.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "player.h"
#include <vector>
#include <string>
#include <queue>
#include "dice.h"
#include "strategy.h"

class Board {
    int posGeese = 7 ;
    int seed = 0;
    std::vector<Tile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    std::vector<Player*> players;
    std::queue<char> playerQueue;
    int curTurn = 0;
    
    // 5 helper function for Board::printBoard()
    std::string ttype(int pos); 
    std::string tval(int pos);
    std::string vfo(int pos);
    std::string efo(int pos);
    std::string gfo(int pos);

    public:
    // ctor
    Board();
    int getCurTurn() const;
    void setCurTurn(int ind);
    void setGeese( int ind );
    int getGeese() const;

    void clearBoard();
    void printBoard();
    void printAllPlayerStatus();
    void printCurPlayerRes();

    void initAttachBoard();
    void initRandBoard();
    void initLoadBoard( std::string file );
    void initSeedBoard( int seed );
    void loadGame( std::string file );
    void loadRes( int posPlayer, int pos, char buildType = 'B' );
    void loadRoad( int posPlayer, int pos );
    std::string saveGame();

    void setDice(bool fair);
    int rollDice(int value = 0); // if roll loaded dice, pass value
    void gainResources(int tileVal);

    bool buildResFree( int posPlayer, int pos );
    void buildRes( int pos );
    void buildRoad( int pos );
    void improveRes( int pos );

    void printUsingChoice();
    int trade( std::string otherplayer, std::string ownResources, std::string otherResource );
    void loseHalf();
    void moveGeese( int pos );

    bool checkWon();

    void endCurTurn();
    
};
