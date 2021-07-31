#include "dice.h"

Dice::Dice(Strategy* strategy, int dicePoint, int seed)
    : strategy{strategy}, dicePoint{dicePoint}, seed{seed} {}

void Dice::setStrategy(Strategy* strategy) {
        this->strategy = strategy;
}

void Dice::roll() {
    strategy->rollDice(dicePoint, seed);
}

int Dice::getPoint() {
    return dicePoint;
}

void Dice::setPoint(int value) {}
