#include "RandomRoboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void RandomRoboto::setConfig(size_t w, size_t h, unsigned e, unsigned p) {
    width = w;
    height = h;
    energy = e;
    power = p;
    //TODO: should we initialize the board or not ?
    // board = vector<vector<Case>>(w, vector<string>(h, EMPTY));
}

string RandomRoboto::action(vector<string> updates) {
    int dX = (rand() % 10 == 0) ? 1 : -1;
    int dY = (rand() % 10 == 0) ? 1 : 0;
    Direction randomDirection(dX, dY);
    return Message::actionMove(randomDirection);
}

string RandomRoboto::name() const {
    return "RandomRoboto";
}

string RandomRoboto::chooseAction() {
    //TODO: Implement RandomRoboto strategy
    return "";
}
