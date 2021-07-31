#include "board.h"
#include <random>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <utility>
#include <iomanip>
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "player.h"
using namespace std;

Board::Board() {
    for ( size_t i = 0; i < 4; i++ ) {
        Player* tmpPlayer = new Player;
        players.emplace_back(tmpPlayer);
    }
    for ( size_t i = 0; i < 19; i++ ) {
        Tile* tmpTile = new Tile{i};
        tiles.emplace_back(tmpTile);
    }
    for ( size_t j = 0; j < 54; j++ ) {
        Vertex* tmpVertex = new Vertex{j};
        vertices.emplace_back(tmpVertex);
    }
    for ( size_t k = 0; k < 72; k++ ) {
        Edge* tmpEdge = new Edge{k};
        edges.emplace_back(tmpEdge);
    }
    playerQueue.push('B');
    playerQueue.push('R');
    playerQueue.push('O');
    playerQueue.push('Y');
}

int Board::getCurTurn() const {return this->curTurn; }
void Board::setCurTurn(int ind) {this->curTurn = ind; }

void Board::clearBoard() {
    for ( size_t i = 0; i < 4; i++ ) {
        delete players[i];
    }
    for ( size_t i = 0; i < 19; i++ ) {
        delete tiles[i];
    }
    for ( size_t j = 0; j < 54; j++ ) {
        delete vertices[j];
    }
    for ( size_t k = 0; k < 72; k++ ) {
        delete edges[k];
    }
}


void Board::initAttachBoard() {
    // resource type on Tile still need to be set
    // attach Vertex neighbours to Tile
    tiles[0]->attach(vertices[0]);              // tile 0
    tiles[0]->attach(vertices[1]);
    tiles[0]->attach(vertices[3]);
    tiles[0]->attach(vertices[4]);
    tiles[0]->attach(vertices[8]);
    tiles[0]->attach(vertices[9]);

    for (int i = 1; i < 3; i++){                // tile 1,2
        tiles[i]->attach(vertices[i*2]);
        tiles[i]->attach(vertices[i*2+1]);
        tiles[i]->attach(vertices[i*2+5]);
        tiles[i]->attach(vertices[i*2+6]);
        tiles[i]->attach(vertices[i*2+11]);
        tiles[i]->attach(vertices[i*2+12]);
    }

    for (int i = 3; i < 16; i++) {               // tile 3-15
        int j = 0;
        if (i > 5) j += 1;
        if (i > 7) j += 1;
        if (i > 10) j += 1;
        if (i > 12) j += 1;
        tiles[i]->attach(vertices[i*2+j]);
        tiles[i]->attach(vertices[i*2+1+j]);
        tiles[i]->attach(vertices[i*2+6+j]);
        tiles[i]->attach(vertices[i*2+7+j]);
        tiles[i]->attach(vertices[i*2+12+j]);
        tiles[i]->attach(vertices[i*2+13+j]);
    }
 
    for (int i = 16; i < 18; i++) {               // tile 16,17
        tiles[i]->attach(vertices[i*2+5]);
        tiles[i]->attach(vertices[i*2+6]);
        tiles[i]->attach(vertices[i*2+11]);
        tiles[i]->attach(vertices[i*2+12]);
        tiles[i]->attach(vertices[i*2+16]);
        tiles[i]->attach(vertices[i*2+17]);
    }

    tiles[18]->attach(vertices[44]);            // tile 18
    tiles[18]->attach(vertices[45]);
    tiles[18]->attach(vertices[49]);
    tiles[18]->attach(vertices[50]);
    tiles[18]->attach(vertices[52]);
    tiles[18]->attach(vertices[53]);


    // attach Edge neighbours to Vertex
    vertices[0]->attachEdgeDoubly(edges[0]);
    vertices[0]->attachEdgeDoubly(edges[1]); 

    vertices[1]->attachEdgeDoubly(edges[0]);
    vertices[1]->attachEdgeDoubly(edges[2]);

    vertices[2]->attachEdgeDoubly(edges[3]);
    vertices[2]->attachEdgeDoubly(edges[5]);

    for (int i = 3; i < 5; i++) {
        vertices[i]->attachEdgeDoubly(edges[i-2]);
        vertices[i]->attachEdgeDoubly(edges[i]);
        vertices[i]->attachEdgeDoubly(edges[i+3]);
    }

    vertices[5]->attachEdgeDoubly(edges[4]);
    vertices[5]->attachEdgeDoubly(edges[8]);

    vertices[6]->attachEdgeDoubly(edges[9]);
    vertices[6]->attachEdgeDoubly(edges[12]);

    for (int i = 7; i < 11; i++) {
        int j = 2;
        if (i > 8) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i-2]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+6]);
    }

    vertices[11]->attachEdgeDoubly(edges[11]);
    vertices[11]->attachEdgeDoubly(edges[17]);

    vertices[12]->attachEdgeDoubly(edges[12]);
    vertices[12]->attachEdgeDoubly(edges[20]);

    for (int i = 13; i < 17; i++) {
        int j = 5;
        if (i > 13) j -= 1;
        if (i > 15) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+8]);
    }

    vertices[17]->attachEdgeDoubly(edges[17]);
    vertices[17]->attachEdgeDoubly(edges[25]); 

    for (int i = 18; i < 24; i++) {
        int j = 8;
        if (i > 18) j -= 1;
        if (i > 20) j -= 1;
        if (i > 22) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+2]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+11]);
    }

    vertices[24]->attachEdgeDoubly(edges[29]);
    vertices[24]->attachEdgeDoubly(edges[37]);

    for (int i = 25; i < 29; i++) {
        int j = 10;
        if (i > 25) j -= 1;
        if (i > 27) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+5]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+13]);
    }

    vertices[29]->attachEdgeDoubly(edges[34]);
    vertices[29]->attachEdgeDoubly(edges[42]);

    for (int i = 30; i < 36; i++) {
        int j = 13;
        if (i > 30) j -= 1;
        if (i > 32) j -= 1; 
        if (i > 34) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+7]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+16]);
    }

    vertices[36]->attachEdgeDoubly(edges[46]);
    vertices[36]->attachEdgeDoubly(edges[54]);

    for (int i = 37; i < 41; i++) {
        int j = 15;
        if (i > 37) j -= 1;
        if (i > 39) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+10]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+18]);
    }

    vertices[41]->attachEdgeDoubly(edges[51]);
    vertices[41]->attachEdgeDoubly(edges[59]);

    vertices[42]->attachEdgeDoubly(edges[54]);
    vertices[42]->attachEdgeDoubly(edges[60]);

    for (int i = 43; i < 47; i++) {
        int j = 17;
        if (i > 44) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+12]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+20]);
    }

    vertices[47]->attachEdgeDoubly(edges[59]);
    vertices[47]->attachEdgeDoubly(edges[62]);

    vertices[48]->attachEdgeDoubly(edges[63]);
    vertices[48]->attachEdgeDoubly(edges[67]);

    for (int i = 49; i < 51; i++) { 
        vertices[i]->attachEdgeDoubly(edges[i+15]);
        vertices[i]->attachEdgeDoubly(edges[i+18]);
        vertices[i]->attachEdgeDoubly(edges[i+20]);
    }

    vertices[51]->attachEdgeDoubly(edges[66]);
    vertices[51]->attachEdgeDoubly(edges[68]);

    vertices[52]->attachEdgeDoubly(edges[69]);
    vertices[52]->attachEdgeDoubly(edges[71]);

    vertices[53]->attachEdgeDoubly(edges[70]);
    vertices[53]->attachEdgeDoubly(edges[71]);
}

// Jim Part_________________________________________________________________

char ownerPosToChar( int ownerPos ) {
    switch( ownerPos ) {
        case 0:
            return 'B'; break;
        case 1:
            return 'R'; break;
        case 2:
            return 'O'; break;
        case 3:
            return 'Y'; break;
        default:
            throw "WRONG ownerPos TYPE FOR ownerPosToChar"; return '-'; break;
    }
}


string Board::ttype(int pos) {
    char tileType = tiles[pos]->getResourceType();
    switch( tileType ) {
        case 'H':
            return "  HEAT   "; break;
        case 'W':
            return "  WIFI   "; break;
        case 'E':
            return " ENERGY  "; break;
        case 'B':
            return "  BRICK  "; break;
        case 'G':
            return "  GLASS  "; break;
        case 'P':
            return "  PARK   "; break;
        default:
            cout << "WRONG RESOURCE TYPE FOR Board::ttype" << endl;
            throw -1; break;
    }
}


string Board::tval(int pos) {
    string ret = "  ";
    int tileVal = tiles[pos]->getValue();
    if ( tiles[pos]->getResourceType() == 'P' ) {
        ret += " ";
    } else {
        if ( tileVal < 10 ) ret += " ";
        ret += to_string(tileVal);
    }
    ret += "  ";
    return ret;
}


string Board::vfo(int pos) {
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return "-";}
    string ret = "|";
    if ( vertices[pos]->getOwner() == nullptr ) {
        if ( pos < 10 ) ret += " ";
        ret += to_string(pos);
    } else {
        int ownerPos = vertices[pos]->getOwnerPos();
        ret += ownerPosToChar(ownerPos);
        ret += vertices[pos]->getBuildType();
    }
    ret += "|";
    return ret;
}


string Board::efo(int pos) {
    if ( pos < 0 || pos > 71 ) {cout << "WARNING: edge index out of range" << endl;return "-";}
    string ret;
    if ( edges[pos]->getOwner() == nullptr ) {
        if ( pos < 10 ) ret += " ";
        ret += to_string(pos);
    } else {
        ret += " ";
        int ownerPos = edges[pos]->getOwnerPos();
        ret += ownerPosToChar(ownerPos);
    }
    return ret;
}


string Board::gfo(int pos) {
    if (posGeese == pos) return "  GEESE  ";
    return "         ";
}


void Board::printBoard() {
    cout << "                          "<<vfo(0)<<"--"<<efo(0)<<"--"<<vfo(1)<<endl;
    cout << "                            |         |"<<endl;
    cout << "                           "<<efo(1)<<"    0   "<<efo(2)<<endl;
    cout << "                            |"<<ttype(0)<<"|"<<endl;
    cout << "                "<<vfo(2)<<"--"<<efo(3)<<"--"<<vfo(3)<<tval(0)<<vfo(4)<<"--"<<efo(4)<<"--"<<vfo(5)<<endl;
    cout << "                  |         |"<<gfo(0)<<"|         |"<<endl;
    cout << "                 "<<efo(5)<<"    1   "<<efo(6)<<"        "<<efo(7)<<"    2   "<<efo(8)<<endl;
    cout << "                  |"<<ttype(1)<<"|         |"<<ttype(2)<<"|"<<endl;
    cout << "      "<<vfo(6)<<"--"<<efo(9)<<"--"<<vfo(7)<<tval(1)<<vfo(8)<<"--"<<efo(10)<<"--"<<vfo(9)<<tval(2)<<vfo(10)<<"--"<<efo(11)<<"--"<<vfo(11)<< endl;
    cout << "        |         |"<<gfo(1)<<"|         |"<<gfo(2)<<"|         |"<<endl;
    cout << "       "<<efo(12)<<"    3   "<<efo(13)<<"        "<<efo(14)<<"    4   "<<efo(15)<<"        "<<efo(16)<<"    5   "<<efo(17)<<endl;
    cout << "        |"<<ttype(3)<<"|         |"<<ttype(4)<<"|         |"<<ttype(5)<<"|"<< endl;
    cout << "      "<<vfo(12)<<tval(3)<<vfo(13)<<"--"<<efo(18)<<"--"<<vfo(14)<<tval(4)<<vfo(15)<<"--"<<efo(19)<<"--"<<vfo(16)<<tval(5)<<vfo(17)<<endl;
    cout << "        "<<"|"<<gfo(3)<<"|         |"<<gfo(4)<<"|"<<"         "<<"|"<<gfo(5)<<"|"<<endl;
    cout << "       "<<efo(20)<<"        "<<efo(21)<<"    6   "<<efo(22)<<"        "<<efo(23)<<"    7   "<<efo(24)<<"        "<<efo(25) << endl;
    cout << "        |         |"<<ttype(6)<<"|         |"<<ttype(7)<<"|         |" << endl;
    cout << "      "<<vfo(18)<<"--"<<"26"<<"--"<<vfo(19)<<tval(6)<<vfo(20)<<"--"<<"27"<<"--"<<vfo(21)<<tval(7)<<vfo(22)<<"--"<<"28"<<"--"<<vfo(23) << endl;
}


void Board::printAllPlayerStatus() {
    for ( int i = 0; i < 4; i++ ) {
        cout << "Builder ";
        switch( i ) {
            case 0:
                cout << "Blue     "; break;
            case 1:
                cout << "Red      "; break;
            case 2:
                cout << "Orange   "; break;
            case 3:
                cout << "Yellow   "; break;
            default:
                throw "WRONG curTurn TYPE FOR Board::printAllPlayerStatus"; return; break;
        }
        cout << "has " << setfill(' ')  << setw(2) << players[i]->getBuildPoint();
        cout << " building points";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('B') << " BRICK";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('E') << " ENERGY";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('G') << " GLASS";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('H') << " HEAT";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('W') << " WIFI";
        cout << '.' << endl;
    }
}


void Board::printCurPlayerRes() {
    switch( curTurn ) {
        case 0:
            cout << "Blue "; break;
        case 1:
            cout << "Red "; break;
        case 2:
            cout << "Orange "; break;
        case 3:
            cout << "Yellow "; break;
        default:
            throw "WRONG curTurn TYPE FOR Board::printCurPlayerRes"; return; break;
    }
    cout << "has built:" << endl;
    for ( int i = 0; i < 54; i++ ) {
        if ( vertices[i]->getOwnerPos() == curTurn ) {
            cout << setfill(' ')  << setw(2) << i <<" "<< vertices[i]->getBuildType() << endl;
        }
    }
}


bool Board::buildResFree( int pos ) {
    Vertex* destVertex = vertices[pos];
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return false;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return false;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::buildResFree access nullptr to pass ";return false;}
    bool tmp = players[curTurn]->buildResFree(destVertex);
    if (tmp == true) destVertex->setOwnerPos(curTurn);
    return tmp;
}


void Board::buildRes( int pos ) {
    Vertex* destVertex = vertices[pos];
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::buildRes access nullptr to pass ";return;}
    bool tmp = players[curTurn]->buildRes(destVertex);
    if (tmp == true) destVertex->setOwnerPos(curTurn);
    return;
}


void Board::buildRoad( int pos ) {
    Edge* destEdge = edges[pos];
    size_t position = pos;
    if ( pos < 0 || pos > 71 ) {cout << "WARNING: edge index out of range" << endl;return;}
    if ( position > edges.size() - 1 ){cout << "WARNING: edges length wrong" << endl;return;}
    if ( destEdge == nullptr ){cout << "FATAL WARNING: Board::buildRoad access nullptr to pass ";return;}
    bool tmp = players[curTurn]->buildRoad(destEdge);
    if (tmp == true) destEdge->setOwnerPos(curTurn);
    return;
}


void Board::improveRes( int pos ) {
    Vertex* destVertex = vertices[pos];
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::improveRes access nullptr to pass ";return;}
    bool tmp = players[curTurn]->improveRes(destVertex);
    return;
}

//刘书辰____________________________________________________________________

// helper function: generate random number
int myrandom (int i) { return std::rand()%i;}

// helper function: initialize resource vector
std::vector<char> initResourse() {
    std::vector<char> resource(3, 'W');
    resource.insert(resource.end(), 3, 'H');
    resource.insert(resource.end(), 4, 'B');
    resource.insert(resource.end(), 4, 'E');
    resource.insert(resource.end(), 4, 'G');
    resource.emplace_back('P');
    return resource;
}


void Board::initRandBoard() {
    srand(time(0));

    // create resourse vector and shuffle with the above random generated seed
    std::vector<char> resource = initResourse();
    std::random_shuffle(resource.begin(), resource.end(), myrandom);

    //create value vector and shuffle with the above random generated seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::random_shuffle(value.begin(), value.end(), myrandom);

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), 'P') - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);
    
    //create Tile 
    for (int i = 0; i < 19; i++) { 
        tiles[i]->setResourceType(resource[i]);
        tiles[i]->setValue(value[i]); 
    }
}

// 刘书辰
void Board::initSeedBoard( int seed ) {
    // set seed
    unsigned sd = seed;

    // create random resource with seed
    std::vector<char> resource = initResourse();
    std::shuffle(resource.begin(), resource.end(), std::default_random_engine(sd));

    // create random value with seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::shuffle(value.begin(), value.end(), std::default_random_engine(sd));

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), 'P') - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);

    // create Tile
    for (int i = 0; i < 19; i++) { 
        tiles[i]->setResourceType(resource[i]);
        tiles[i]->setValue(value[i]); 
    }
}


// Ivy

// a helper
int intResourceIdentifier(char resource) { 
    switch( resource ) {
        case 'B':
            return 0; break;
        case 'E':
            return 1; break;
        case 'G':
            return 2; break;
        case 'H':
            return 3; break;
        case 'W':
            return 4; break;
        case 'P':
            return 5; break;
    } 
}

char charResourceIdentifier(int resourceType) { 
    switch( resourceType ) {
        case 0:
            return 'B'; break;
        case 1:
            return 'E'; break;
        case 2:
            return 'G'; break;
        case 3:
            return 'H'; break;
        case 4:
            return 'W'; break;
        case 5:
            return 'P'; break;
    } 
}

void Board::initLoadBoard(string file) {
    cout<< "run initLoadBoard" << endl;
    initAttachBoard();
    ifstream fileIn{file};
    int resourceType;
    int value; 
    int i = 0;
    while (fileIn >> resourceType >> value) {
        char type = charResourceIdentifier(resourceType);
        tiles[i]->setResourceType = type;
        tiles[i]->setValue = value;
        i += 1;
    } 
}

void Board::loadGame(string file) {
    cout<< "run loadGame" << endl;
    initAttachBoard();
    ifstream fileIn{file}; 
    string line;
    getline(fileIn, line);
    setCurTurn(stoi(line));                 // curTurn

    int v1,v2,v3,v4,v5,builtRoads,builtHouse;
    string temp;
    int i = 0;
    while (getline(fileIn, line)) {
        istringstream curLine{line};
        curLine >> v1 >> v2 >> v3 >> v4 >> v5 >> temp;
        if (temp != "r") break;             // finish checking player status
        players[i]->setResource('B', v1);
        players[i]->setResource('E', v2);
        players[i]->setResource('G', v3);
        players[i]->setResource('H', v4);
        players[i]->setResource('W', v5);
        while (curLine >> builtRoads) {
            loadRoad(i, builtRoads);
        }
        cin.ignore();
        cin.clear(); 
        char type;
        while (curLine >> v1 >> type) {
            loadRes(i, v1, type);
        }
        i += 1;
    }
    getline(fileIn, line);                  // board
    int resourceType;
    int value; 
    int i = 0;
    while (fileIn >> resourceType >> value) {
        char type = charResourceIdentifier(resourceType);
        tiles[i]->setResourceType = type;
        tiles[i]->setValue = value;
        i += 1;
    } 
    fileIn >> v1;
    setGeese(v1);                           // geese
}

string Board::saveGame() {
    cout<< "run savGame" << endl;
    ostringstream out;
    out << curTurn << endl;                             // <curTurn>
    vector<vector<int>> res;                            // house info
    for ( int i = 0; i < vertices.size(); i++ ) {
        int owner = vertices[i]->getOwnerPos();
        res[owner].emplace_back(i);
    }
    for (int i = 0; i < players.size(); i++) {          // <builder i's Data>
        out << players[i]->getNumResource('B') << " ";
        out << players[i]->getNumResource('E') << " ";
        out << players[i]->getNumResource('G') << " ";
        out << players[i]->getNumResource('H') << " ";
        out << players[i]->getNumResource('W') << " ";   
        // print out roads
        vector<int> roads = players[i]->getEdgeIndex();
        sort(roads.begin(), roads.end());
        out << "r " ;
        for (auto r : roads) {
            out << r << " ";
        }
        // print out residence
        for (auto pos: res[i]){
            char buildType = vertices[pos]->getBuildType();
            out << pos << " " << buildType << " ";
        }
        out << endl;
    }
    for (int i = 0; i < tiles.size(); i++) {            // <board>
        char type = tiles[i]->getResourceType();
        out << intResourceIdentifier(type).first << " ";
        out << tiles[i]->getValue() << " ";
        if (i == tiles.size()-1) out << endl;
    }
    out << posGeese;                                    // <geese>
    return out.str();
}



//刘书辰

void Board::setDice(bool fair) {
    if (fair) {// set loaded strategy
        players[curTurn]->setStrategyState('L');
    } else {
        players[curTurn]->setStrategyState('R');
    }
}

int Board::rollDice(int value) {
    return players[curTurn]->rollDice(value, seed);
}

void Board::gainResources(int tileVal){
    // notify observers of tileVal
    // only notify which has been build
    for ( size_t i = 0; i < tiles.size(); i++ ) {
        if ( tiles[i] == nullptr ) { cout << "WARNING: Board::gainResources dereference nullptr at line:" << __LINE__ << endl; return; }
        if ( tiles[i]->getValue() == tileVal ) {
            tiles[i]->notifyObservers();
        }
    }
}



void Board::trade( string otherplayer, string ownResources, string otherResource ){}
void Board::loseHalf(){}
void Board::moveGeese( int pos ){}

bool Board::checkWon() {
    int points = players[curTurn]->getBuildPoint();
    if (points >= 10) return true;
    return false;
}

void endCurTurn() {
    
}
