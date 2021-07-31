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
    cout << "Board with seed 233: " << endl;
    b.initSeedBoard(233);
    b.printBoard();
    b.printAllPlayerStatus();
    b.printCurPlayerRes();
}
