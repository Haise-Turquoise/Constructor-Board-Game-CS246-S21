#include "board.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "subject.h"
#include "observer.h"
#include "player.h"
#include "dice.h"
#include "strategy.h"
#include <iostream>
using namespace std;

int main() {
    Board b;
    cout << "Board with seed 231: " << endl;
    b.initSeedBoard(231);
    b.printBoard();
    cout << "Board with seed 232: " << endl;
    b.initSeedBoard(232);
    b.printBoard();
    cout << "empty Board with seed 233: " << endl;
    b.initSeedBoard(233);
    b.printBoard();
    b.loadRes(0,14,'T');
    b.loadRes(1,15,'B');
    b.loadRes(2,52,'H');
    b.loadRes(3,37,'B');
    b.loadRes(3,35,'T');
    b.loadRes(2,23,'B');
    b.loadRes(1,45,'H');
    b.loadRes(0,30,'T');
    b.loadRoad(0,14);
    b.loadRoad(0,10);
    b.loadRoad(0,15);
    b.loadRoad(1,62);
    b.loadRoad(1,59);
    b.loadRoad(1,51);
    b.loadRoad(1,51);
    b.loadRoad(3,63);
    b.loadRoad(3,64);
    b.loadRoad(3,61);
    b.loadRoad(3,65);
    b.loadRoad(3,68);
    cout << "Loaded Board with seed 233: " << endl;
    b.printBoard();
    b.printAllPlayerStatus();
    b.printCurPlayerRes();
}
