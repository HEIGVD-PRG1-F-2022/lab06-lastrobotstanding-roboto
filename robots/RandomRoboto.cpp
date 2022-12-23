#include "RandomRoboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

string RandomRoboto::action(vector<string> updates) {
}

string RandomRoboto::name() const {
    return "RandomRoboto";
}

string RandomRoboto::chooseAction(UpdatesPack pack) {
    int dX, dY;
    if ((rand() % 10 == 0)) {
        dX = (rand() % 10 == 0) ? 1 : -1;
        dY = (rand() % 10 == 0) ? 1 : 0;
        return Message::actionMove(Direction(dX, dY));
    } else {
        dX = -1;
        dY = 1;
        return Message::actionMove(Direction(dX, dY));
    }
}
