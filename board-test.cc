#include "board.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "subject.h"
#include "observer.h"
#include "player.h"
#include <iostream>
using namespace std;

int main() {
    Board b;
    cout << "board with seed 231: " << endl;
    b.initSeedBoard(231);
    cout << "board with seed 232: " << endl;
    b.initSeedBoard(232);
    cout << "board with seed 233: " << endl;
    b.initSeedBoard(233);
    b.printAllPlayerStatus();
    b.printCurPlayerRes();
}
