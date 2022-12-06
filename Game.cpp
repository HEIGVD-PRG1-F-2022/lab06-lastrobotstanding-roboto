#include "Game.h"
#include <cmath>
#include <libdio/display.h>
#include <librobots/Direction.h>
#include <librobots/Message.h>
#include <librobots/Position.h>
#include <librobots/Robot.h>
#include <librobots/RobotState.h>
#include <random>
#include <string>
#include <vector>

const int BASE_ENERGY = 10;
const int BASE_POWER = 1;

//Function taken from this snippet https://stackoverflow.com/a/19728404
int getRandomNumber(int min, int max) {
    std::random_device rd;                           // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());                          // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max);// Guaranteed unbiased
    auto random_integer = uni(rng);
    return random_integer;
}

Game::Game(unsigned nbRobots) : nbRobots(nbRobots) {
    this->nbRobots = nbRobots;
    size = sqrt(nbRobots) * 10;
}

void Game::start() {
    Display::DString d(Display::Color::GREEN);
    d << "Welcome in LastRobotStanding, the fight has started...\n";
    d.print();
    generateRobots();

    //game loop
    string boardUpdate;
    vector<string> updates;
    vector<string> moves;
    vector<string> attacks;
    string action;
    size_t iterationWithoutAttack = 0;
    bool someRobotsAttackedInThisIteration;
    const int MAXIMUM_ITERATION_WITHOUT_ATTACK = 100;

    while (iterationWithoutAttack < MAXIMUM_ITERATION_WITHOUT_ATTACK * nbRobots && getLivingRobots().size() > 0) {
        someRobotsAttackedInThisIteration = false;

        boardUpdate = "board " + computeBoardAsString();
        for (RobotState state: robots) {
            updates.push_back(boardUpdate);
            //action = state.askAction(updates);
            updates.clear();
        }

        //Get and apply attacks
        for (RobotState state: getLivingRobots()) {
            Message message = state.getAction();
            if (message.msg == MessageType::ActionAttack) {
                Direction attackedRobotDirection = message.robots.at(0);
                Position attackedRobotPosition = state.getPosition() + attackedRobotDirection;

                //Look for a robot on the position attackedRobotPosition (if there is no robot, nothing will happen)
                for (RobotState otherRobot: getLivingRobots()) {
                    if (state.getPosition() == attackedRobotPosition) {
                        someRobotsAttackedInThisIteration = true;
                        otherRobot.actionAttack(state, attackedRobotPosition);
                        break;//don't look for other robots as it's impossible to have other robots on the same cell (at this point)
                    }
                }
            }
        }

        //Get and apply moves
        for (RobotState state: getLivingRobots()) {
            Message message = state.getAction();
            if (message.msg == MessageType::ActionMove) {
                state.actionMove(message.robots.at(0));//apply the move
            }
            //TODO: check if there is another robot on the same position!
            //TODO: check if there is a bonus at this position
        }

        if (someRobotsAttackedInThisIteration) {
            iterationWithoutAttack++;
        }
        printBoard();
        Display::clearScreen();
    }
}

void Game::generateRobots() {
    int randomX, randomY;
    for (unsigned i = 0; i < nbRobots; i++) {
        randomX = getRandomNumber(0, (int) size - 1);
        randomY = getRandomNumber(0, (int) size - 1);
        Position pos(randomX, randomY, size, size);
        Roboto unRobot(size, size, BASE_ENERGY, BASE_POWER);
        robots.push_back(RobotState(&unRobot, pos, size, BASE_ENERGY, BASE_POWER));
    }
}

vector<RobotState> Game::getLivingRobots() const {
    vector<RobotState> filteredList;

    for (RobotState state: robots) {
        if (state.isDead() == false) {
            filteredList.push_back(state);
        }
    }
    return filteredList;
}

vector<vector<string>> Game::buildDynamicBoard() {
    vector<vector<string>> board = vector<vector<string>>(size, vector<string>(size, " "));

    //For each RobotState we add them in the board with their number
    int index = 1;
    for (RobotState &state: robots) {
        string &cell = board.at(state.getPosition().getX()).at(state.getPosition().getY());
        cell = (cell != " ") ? "C" : to_string(index);//a C char is displayed when 2 robots (or more) are on the same cell
        index++;
    }
    return board;
}

void Game::printBoard() {
    //Create an empty board
    vector<vector<string>> board = buildDynamicBoard();

    for (auto line: board) {
        for (auto cell: line) {
            cout << cell;
        }
        cout << endl;
    }
    //TODO: refactor with displayGrid from
    // Display::DString h;
    // h.displayGrid<string>(board, true);
    // h.print();
}

string Game::computeBoardAsString() {
    vector<vector<string>> board = buildDynamicBoard();
    string msg;
    for (auto line: board) {
        for (auto cell: line) {
            msg += cell;
        }
    }
    return msg;
}