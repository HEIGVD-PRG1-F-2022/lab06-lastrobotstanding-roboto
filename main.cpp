#include "Game.h"
#include "helper.h"
#include <libdio/display.h>
#include <libdio/input.h>

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ROBOT_NUMBER = 2;
int main() {
    vector<RobotPack> robotPacks = {{"Roboto", 1}, {"RandomRoboto", 1}};

    srand(time(0));
    Display::init();
    Game game(ROBOT_NUMBER);
    game.start(robotPacks);
}
