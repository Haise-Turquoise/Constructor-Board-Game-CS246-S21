#include "player.h"
#include <iostream>
#include <random>
#include <vector>
#include  <iterator>
using namespace std;


Player::Player(): 
    numHeat{0}, numWifi{0}, numEnergy{0}, numBrick{0}, numGlass{0}
    ,numBuild{0}, buildPoints{0} {}
Player::~Player() {}

int Player::getNumResource(char resourceType) { 
    switch( resourceType ) {
        case 'H':
            return numHeat; break;
        case 'W':
            return numWifi; break;
        case 'E':
            return numEnergy; break;
        case 'B':
            return numBrick; break;
        case 'G':
            return numGlass; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::getNumResource";
            return -1; break;
    }
}
int Player::getNumBuild() { return numBuild; }
int Player::getBuildPoint() { return buildPoints; }

// WARNING: need to consider whether you are allowed build here (initial free build or nearby road)
void Player::buildRes( Vertex* ptrv ) {
    if ( ptrv == nullptr ) {cout << "FATAL WARNING: Player::buildRes pass a nullptr ";return;}
    if ( numBrick < 1 || numEnergy < 1 || numGlass < 1 || numWifi < 1 ) {cout << "WARNING: resource not enough for building residence" << endl;return;}
    if ( ptrv->getBuildType() != '-' ) {cout << "WARNING: this place is occupied by other or self" << endl;return;}
    if ( ptrv->getIndex() == -1 ) {cout << "WARNING: vertex index unitialized" << endl;return;}
    if ( ptrv->getIndex() < 0 || ptrv->getIndex() > 53 ) {cout << "WARNING: vertex index out of range" << endl;return;}
    // update Player field
    numBrick -= 1; numEnergy -= 1; numGlass -= 1; numWifi -= 1;
    numBuild += 1; buildPoints += 1;
    ownVertices.emplace_back(ptrv);
    // update Vertex field
    ptrv->setBuildType('B');
    // WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
    ptrv->setOwner(this);
    cout<< "line:" << __LINE__ << endl;
}



void Player::buildRoad( Edge* ptre ) {  }
void Player::improveRes( Vertex* ptrv ) {  }

void Player::addResource(char resourceType) {}
void Player::decResource(char resourceType) {} // need to check non-0
bool Player::existResource() {return false;}

char Player::beStolen() {return '-';}
int Player::rollDice( int value ) {}




void Player::addResource(char resourceType) {
    switch( resourceType ) {
        case 'H':
            numHeat +=1; break;
        case 'W':
            numWifi +=1; break;
        case 'E':
            numEnergy +=1; break;
        case 'B':
            numBrick +=1; break;
        case 'G':
            numGlass +=1; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::addResource"; break;
    }
}
int Player::rollDice( int value ) { return value; }


// helper function: generate resource vector
vector<char> Player::generateResBoard() {
    vector<char> generateBoard(numHeat,'H');
    generateBoard.insert(generateBoard.end(), numWifi, 'W');
    generateBoard.insert(generateBoard.end(), numEnergy, 'E');
    generateBoard.insert(generateBoard.end(), numBrick, 'B');
    generateBoard.insert(generateBoard.end(), numGlass, 'G');
    return generateBoard;
}


char Player::beStolen(int seed) {
    vector<char> generateBoard = generateResBoard();
    int totalRes = numHeat + numWifi + numEnergy + numBrick + numGlass;
    unsigned sd = seed;
    std::default_random_engine g{sd};
    std::uniform_int_distribution<int> distribution(0,totalRes - 1);
    int ranIdx = distribution(g);
    return generateBoard[ranIdx];
}

void Player::loseHalfResource(int seed) {
    unsigned sd = seed;
    vector<char> generateBoard = generateResBoard();
    std::shuffle(generateBoard.begin(), generateBoard.end(), std::default_random_engine(sd));
    // the first half of generateResBoard
    size_t half_size = generateBoard.size() / 2;
    vector<char> firstHalf(generateBoard.begin(), generateBoard.begin() + half_size);
    // update number of resource
    numHeat = count(firstHalf.begin(), firstHalf.end(), 'H');
    numWifi = count(firstHalf.begin(), firstHalf.end(), 'W');
    numEnergy = count(firstHalf.begin(), firstHalf.end(), 'E');
    numBrick = count(firstHalf.begin(), firstHalf.end(), 'B');
    numGlass = count(firstHalf.begin(), firstHalf.end(), 'G');
}
