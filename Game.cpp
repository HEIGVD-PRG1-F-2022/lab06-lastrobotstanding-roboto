#include "Game.h"
#include "RobotState.h"
#include "build/_deps/libdio-src/include/libdio/display.h"
#include <libdio/display.h>
#include <random>
#include <string>
#include <vector>
const int BASE_ENERGY = 10;
const int BASE_POWER = 1;

//Function taken from this snippet https://stackoverflow.com/a/19728404
int getRandomNumber(int min, int max) {
    // std::random_device rd;                           // Only used once to initialise (seed) engine
    // std::mt19937 rng(rd());                          // Random-number engine used (Mersenne-Twister in this case)
    // std::uniform_int_distribution<int> uni(min, max);// Guaranteed unbiased
    // auto random_integer = uni(rng);
    // return random_integer;
    return min + (rand() % static_cast<int>(max - min + 1));
}

Game::Game(unsigned nbRobots) : nbRobots(nbRobots) {
    this->nbRobots = nbRobots;
    size = nbRobots * 10;
}

void Game::start() {
    Display::DString d(Display::Color::GREEN);
    d << "Welcome in LastRobotStanding, the fight has started...\n";
    d.print();
    generateRobots();
    d << "robots setuped !!";
    d.print();
    //game loop
    // while (true) {
    printBoard();
    // }
}

void Game::generateRobots() {
    int randomX, randomY;
    for (unsigned i = 0; i < nbRobots; i++) {
        randomX = getRandomNumber(0, (int) size - 1);
        randomY = getRandomNumber(0, (int) size - 1);
        robots.push_back(RobotState(randomX, randomY, BASE_ENERGY, BASE_POWER, size, size));
        cout << "new robot" << randomX;
    }
}

void Game::printBoard() {
    //Create an empty board
    vector<vector<string>> board = vector<vector<string>>(size, vector<string>(size, " "));

    //For each RobotState we add them in the board with their number
    int index = 1;
    for (RobotState &state: robots) {
        string &cell = board.at(state.getX()).at(state.getY());
        cell = (cell != " ") ? "C" : to_string(index);//a C char is displayed when 2 robots (or more) are on the same cell
        index++;
    }

    Display::displayGrid(board);
}