#include "Game.h"
#include <libdio/display.h>
#include <libdio/input.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ROBOT_NUMBER = 2;
int main() {
    Display::init();
    Game game(ROBOT_NUMBER);
    game.start();
}
