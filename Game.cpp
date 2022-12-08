#include "Game.h"
#include "helper.h"
#include <chrono>
#include <cmath>
#include <libdio/display.h>
#include <librobots/Direction.h>
#include <librobots/Message.h>
#include <librobots/Position.h>
#include <librobots/Robot.h>
#include <librobots/RobotState.h>
#include <random>
#include <string>
#include <thread>
#include <vector>

const int BASE_ENERGY = 10;
const int BASE_POWER = 1;

using namespace std;

Game::Game(unsigned nbRobots) : nbRobots(nbRobots) {
    size = sqrt(nbRobots) * 10;
}

void Game::start() {
    Display::DString d(Display::Color::GREEN);
    d << "Welcome in LastRobotStanding, the fight has started...\n";
    d.print();
    generateRobots();

    //game loop
    size_t iterationWithoutAttack = 0;
    bool someRobotsAttackedInThisIteration;
    const int MAXIMUM_ITERATION_WITHOUT_ATTACK = 100;
    const std::chrono::milliseconds SLEEP_TIME_BETWEEN_LOOP(100);

    while (iterationWithoutAttack < MAXIMUM_ITERATION_WITHOUT_ATTACK * nbRobots && getLivingRobots().size() > 1) {
        someRobotsAttackedInThisIteration = false;

        //Build a list of all living robots positions
        vector<Position> positions;
        for (const RobotState *state: getLivingRobots()) {
            positions.push_back(state->getPosition());
        }

        //Call action() on all robots with the board update (other updates are already present in the RobotState object)
        size_t index = 0;
        for (RobotState *state: getLivingRobots()) {
            //cout << "board msg: " << Message::updateBoard(positions).at(index) << " and index " << index << endl;

            state->sendUpdate(Message::updateBoard(positions).at(index));
            cout << endl;
            //switch

            cout << "\x1b[38;5;40m" << index << " - Robot: " << state->getPosition() << " - Energy: " << state->getEnergy() << " - Power: " << state->getPower() << " - Move: " << (int) state->getAction().msg << "\x1b[38;5;15m" << endl;
            index++;
            //setcolor white
        }

        //Get and apply attacks
        //TODO: should state be a const ref ??
        for (RobotState *state: getLivingRobots()) {
            Message message = state->getAction();

            if (message.msg == MessageType::ActionAttack) {
                Direction attackedRobotDirection = message.robots.at(0);
                Position attackedRobotPosition = state->getPosition() + attackedRobotDirection;

                //Look for a robot on the position attackedRobotPosition (if there is no robot, nothing will happen)
                for (RobotState *otherRobot: getLivingRobots()) {
                    if (state->getPosition() == attackedRobotPosition) {
                        someRobotsAttackedInThisIteration = true;
                        otherRobot->actionAttack(*state, attackedRobotPosition);
                        break;//don't look for other robots as it's impossible to have other robots on the same cell (at this point)
                    }
                }
            }
        }

        //Get and apply moves
        for (RobotState *state: getLivingRobots()) {
            Message message = state->getAction();

            if (message.msg == MessageType::ActionMove) {
                state->actionMove(message.robots.at(0));//apply the move
            }
            //TODO: check if there is another robot on the same position!
            //TODO: check if there is a bonus at this position
        }

        if (!someRobotsAttackedInThisIteration) {
            iterationWithoutAttack++;
        }
        printBoard();
        std::this_thread::sleep_for(SLEEP_TIME_BETWEEN_LOOP);//little sleep before next reload

        Display::clearScreen();
    }
}

void Game::generateRobots() {
    int randomX, randomY;
    for (unsigned i = 0; i < nbRobots; i++) {
        randomX = getRandomNumber(0, (int) size - 1);
        randomY = getRandomNumber(0, (int) size - 1);
        Position pos(randomX, randomY, size, size);
        // Roboto unRobot = new Roboto();
        // unRobot.setConfig(size, size, BASE_ENERGY, BASE_POWER);
        // Roboto unRobot(size, size, BASE_ENERGY, BASE_POWER);
        Roboto *robot = new Roboto(size, size, BASE_ENERGY, BASE_POWER);
        robots.push_back(RobotState(robot, pos, size, BASE_ENERGY, BASE_POWER));
    }
}

vector<RobotState *> Game::getLivingRobots() {
    vector<RobotState *> filteredList;

    //TODO: refactor with copy_if()
    for (RobotState &state: robots) {
        if (!state.isDead()) {
            filteredList.push_back(&state);
        }
    }
    return filteredList;
}

vector<vector<string>> Game::buildDynamicBoard() {
    vector<vector<string>> board = vector<vector<string>>(size, vector<string>(size, " "));

    //For each RobotState we add them in the board with their number
    int index = 1;
    for (RobotState *state: getLivingRobots()) {
        string &cell = board.at(state->getPosition().getX()).at(state->getPosition().getY());
        cell = (cell != " ") ? "C" : to_string(index);//a C char is displayed when 2 robots (or more) are on the same cell
        index++;
    }
    return board;
}

void Game::printBoard() {
    //Create an empty board
    vector<vector<string>> board = buildDynamicBoard();

    //TODO: colorize cases depending on the robot name to differient robot classes
    Display::DString d(Display::Color::GREEN);
    d << "LastRobotStanding - Game in progress...\n\n";
    d.setColor(Display::Color::WHITE);
    d << Display::displayGrid<string>(board, false);
    d.print();

    //TODO: call the print stats method here
}