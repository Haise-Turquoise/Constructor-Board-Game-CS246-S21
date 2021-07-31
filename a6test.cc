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
    b.initSeedBoard(231);
    b.printAllPlayerStatus();
    b.printCurPlayerRes();
}

