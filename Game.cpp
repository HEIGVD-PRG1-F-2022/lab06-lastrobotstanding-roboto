#include "Game.h"
#include "helper.h"
#include "robots/RandomRoboto.h"
#include "robots/Roboto.h"
#include <algorithm>
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
//#include <windows.h>
#include <iomanip>

const int BASE_ENERGY = 10;
const int BASE_POWER = 1;

using namespace std;

Game::Game(unsigned nbRobots) : nbRobots(nbRobots) {
    size = (size_t) sqrt(nbRobots) * 10;
}

void Game::start(vector<RobotPack> robotPacks) {
    Display::DString d(Display::Color::GREEN);
    d << "Welcome in LastRobotStanding, the fight has started...\n";
    d.print();
    generateRobots(robotPacks);

    //game loop
    size_t iterationWithoutAttack = 0;
    bool someRobotsAttackedInThisIteration;
    const int MAXIMUM_ITERATION_WITHOUT_ATTACK = 100;
    unsigned iterationCount = 0;
    const std::chrono::milliseconds SLEEP_TIME_BETWEEN_LOOP(50);

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
            state->sendUpdate(Message::updateBoard(positions).at(index));
            cout << endl;
            index++;
        }

        //Get and apply attacks
        for (const RobotState *state: getLivingRobots()) {
            Message message = state->getAction();

            if (message.msg == MessageType::ActionAttack) {
                Direction attackedRobotDirection = message.robots.at(0);
                Position attackedRobotPosition = state->getPosition() + attackedRobotDirection;

                //Look for a robot on the position attackedRobotPosition (if there is no robot, nothing will happen)
                for (RobotState *otherRobot: getLivingRobots()) {
                    if (otherRobot->getPosition() == attackedRobotPosition) {
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
        }

        //After moves, check collisions (2 robots on the same case) and apply rules of collision
        vector<RobotState *> livingRobots = getLivingRobots();
        int count = 0;
        for (size_t i = 0; i < livingRobots.size(); i++) {
            RobotState *oneRobot = livingRobots.at(i);//TODO: should we declare the variable before ?
            for (size_t j = i + 1; j < livingRobots.size(); j++) {
                RobotState *otherRobot = livingRobots.at(j);

                //If 2 robots are on the same position, manage collisions
                if (oneRobot->getPosition() == otherRobot->getPosition()) {
                    oneRobot->checkCollision(*otherRobot);//check and apply collision
                }
                count++;
            }
        }

        //TODO: check if there is a bonus at this position

        if (!someRobotsAttackedInThisIteration) {
            iterationWithoutAttack++;
        }

        printBoard(iterationCount);
        std::this_thread::sleep_for(SLEEP_TIME_BETWEEN_LOOP);//little sleep before next reload

        iterationCount++;
    }

    //TODO: display the winner
    printBoard(iterationCount);
    vector<RobotState *> finalLivingRobots = getLivingRobots();
    if (finalLivingRobots.size() == 1) {
        d.setColor(Display::Color::ORANGE);
        d << "The winner is " << finalLivingRobots.at(0)->getName() << "\n";
    } else {
        d.setColor(Display::Color::BLUE);
        d << "The game stopped because " << (100 * nbRobots) << " turns have happened without any attack...\n";
        unsigned index = 0;
        for (RobotState *finalRobot: finalLivingRobots) {
            d << index << ". " << finalRobot->getName();
            printStat(*finalRobot, index);
            index++;
        }
    }

    d.print();

    //system("pause");
}

void Game::generateRobots(vector<RobotPack> robotPacks) {
    for (const RobotPack &pack: robotPacks) {
        int randomX, randomY;
        for (int i = 0; i <= pack.number; i++) {
            randomX = getRandomNumber(0, (int) size - 1);
            randomY = getRandomNumber(0, (int) size - 1);
            Position pos(randomX, randomY, size, size);

            if (pack.className == "RandomRoboto") {
                auto *robot = new RandomRoboto();
                robot->setConfig(size, size, BASE_ENERGY, BASE_POWER);
                robots.push_back(RobotState(robot, pos, size, BASE_ENERGY, BASE_POWER));
            } else if (pack.className == "Roboto") {
                auto *robot = new Roboto();
                robot->setConfig(size, size, BASE_ENERGY, BASE_POWER);
                robots.push_back(RobotState(robot, pos, size, BASE_ENERGY, BASE_POWER));
            }
        }
    }
}

vector<RobotState *> Game::getLivingRobots() {
    vector<RobotState *> filteredList;

    //TODO: refactor with copy_if()
    // doesn't work with isDead(), needs object
    // copy_if(robots.begin(), robots.end(), filteredList.begin(), RobotState::isDead());
    for (RobotState &state: robots) {
        if (!state.isDead()) {
            filteredList.push_back(&state);
        }
    }
    return filteredList;
}

vector<vector<Display::DString>> Game::buildDynamicBoard() {
    vector<vector<Display::DString>> board = vector<vector<Display::DString>>(size, vector<Display::DString>(size, Display::DString()));

    //For each RobotState we add them in the board with their number
    int index = 1;
    //TODO: use livingRobots of the last turn
    for (RobotState *state: getLivingRobots()) {
        Display::DString &cell = board.at(state->getPosition().getX()).at(state->getPosition().getY());
        cell.setColor(Display::Color::GREEN);
        cell << to_string(index);//a C char is displayed when 2 robots (or more) are on the same cell
        index++;
    }
    return board;
}

void Game::printBoard(unsigned iterationCount) {
    //Create an empty board
    vector<vector<Display::DString>> board = buildDynamicBoard();

    Display::clearScreen();

    //TODO: use cursor position to have a smooth animation
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    // => only works on WIN32 + when used, glitch at the end of the game => displays extra lines

    //TODO: colorize cases depending on the robot name to different robot classes
    Display::DString d(Display::Color::GREEN);
    d << "LastRobotStanding - Game in progress...\n";
    d.setColor(Display::Color::WHITE);
    d << Display::displayGrid<Display::DString>(board, true);
    d.print();

    cout << "Tour " << iterationCount << endl;
    printStats();
}

void Game::printStats() {
    cout << "id " << setw(14) << left << "Name "  << setw(5) << left << "pos"
    << "Energy " << "Power " << "Move/Cause of death" << endl;
    unsigned index = 1;
    for(RobotState &state: robots){
        printStat(state, index);
        index++;
    };
}

void Game::printStat(RobotState state, unsigned index) {
    Display::DString stat;
    ostringstream stream;
    stream << setw(2) << index << " " << setw(12) << left << state.getName() << " "
           << state.getPosition() << " "
           << setw(6) << left << state.getEnergy() << " "
           << setw(5) << left << state.getPower() << " ";
    if (state.isDead()) {
        stat.setColor(Display::Color::RED);
        stream << state.getDeathCause() << endl;
    } else {
        stat.setColor(Display::Color::GREEN);
        stream << state.getAction().getMessageType()
               << " (" << setw(2) << state.getAction().robots[0].getdX()
               << "," << setw(2) << state.getAction().robots[0].getY() << ")" << endl;
    }
    stat << stream.str();
    stat.print();
}