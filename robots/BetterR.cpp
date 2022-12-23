#include "BetterR.h"
#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

string BetterR::action(vector<string> updates) {
    return chooseAction(receiveUpdates(updates));
}

string BetterR::name() const {
    return "BetterR";
}

string BetterR::chooseAction(UpdatesPack pack) {


    return Message::actionMove(Direction(-1, 0));
}
