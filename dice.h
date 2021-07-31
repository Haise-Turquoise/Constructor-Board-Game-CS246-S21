#ifndef __DICE_H__
#define __DICE_H__
#include "strategy.h"


// use of Dice:
// Dice dice = Dice{new DiceLoad, pointWeWant};   --- roll loaded dice
// Dice dice = Dice{new DiceRand, 0 (placeholder), seed};       --- roll random dice
// strategy should be wrapped insmart pointer


class Dice {
    Strategy* strategy;
    int dicePoint;
    int seed;
    public:
    Dice(Strategy* strategy, int dicePoint = 0, int seed = 0);
    void setStrategy(Strategy* strategy);
    void roll();
    void setPoint(int value);
    int getPoint();
};

#endif
