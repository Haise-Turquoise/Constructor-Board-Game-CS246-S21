#include "strategy.h"
#include <random>

Strategy::~Strategy() {}

void DiceRand::rollDice(int& dicePoint, int seed) {
    unsigned sd = seed;
    std::default_random_engine g{sd};
    std::uniform_int_distribution<int> distribution(2,12);
    dicePoint = distribution(g);
}

void DiceLoad::rollDice(int& dicePoint, int seed) { }
