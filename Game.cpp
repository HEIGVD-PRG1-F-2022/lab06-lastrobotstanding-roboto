/*
-----------------------------------------------------------------------------------
Nom du fichier  : Game.cpp
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#include "Game.h"
#include "helper.h"
#include "robots/BetterR.h"
#include "robots/RandomRoboto.h"
#include "robots/Roboto.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <libdio/display.h>
#include <librobots/Bonus.h>
#include <librobots/Direction.h>
#include <librobots/Message.h>
#include <librobots/Position.h>
#include <librobots/Robot.h>
#include <librobots/RobotState.h>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

const int BASE_ENERGY = 10;
const int BASE_POWER = 1;
const char CELL_BONUS_CHAR = 'B';

using namespace std;

Game::Game(unsigned nbRobots) : nbRobots(nbRobots) {
    //Seed randomness and init console
    srand(time(0));
    Display::init();
    size = (size_t) sqrt(nbRobots) * 10;
}

string Game::start(vector<RobotPack> robotPacks, bool displayMode) {
    generateRobots(robotPacks);

    //game loop
    size_t iterationWithoutAttack = 0;
    bool someRobotsAttackedInThisIteration;
    const int MAXIMUM_ITERATION_WITHOUT_ATTACK = 100;
    unsigned iterationCount = 0;
    const std::chrono::milliseconds SLEEP_TIME_BETWEEN_LOOP(100);
    const unsigned BONUS_MAX_ENERGY = 10;
    const unsigned BONUS_MAX_POWER = 3;
    vector<Position> positions;    //list of positions of all living robots
    vector<Position> boniPositions;//list of all positions of bonus
    size_t index = 0;
    vector<RobotState *> livingRobots;

    while (iterationWithoutAttack < MAXIMUM_ITERATION_WITHOUT_ATTACK * nbRobots && getLivingRobots().size() > 1) {
        someRobotsAttackedInThisIteration = false;
        iterationCount++;

        livingRobots = getLivingRobots();//load the list the first time

        //Build a list of all living robots positions
        positions.clear();
        for (const RobotState *state: livingRobots) {
            positions.push_back(state->getPosition());
        }
        //Build a list of all bonus positions
        boniPositions.clear();
        for (auto b: boni) {
            boniPositions.push_back(b.pos);
        }
        //Call action() on all robots with the board update (other updates are already present in the RobotState object)
        index = 0;
        vector<string> boardsAsString = Message::updateBoard(positions, boniPositions);
        for (RobotState *state: livingRobots) {
            //Send the board update with the own context for each robot, and ask for the action
            state->sendUpdate(boardsAsString.at(index));
            index++;
        }

        //Get and apply attacks
        for (const RobotState *state: livingRobots) {
            Message message = state->getAction();

            if (!state->isDead() && message.msg == MessageType::ActionAttack) {
                Direction attackedRobotDirection = message.robots.at(0);
                Position attackedRobotPosition = state->getPosition() + attackedRobotDirection;

                //Look for a robot on the position attackedRobotPosition (if there is no robot, nothing will happen)
                for (RobotState *otherRobot: livingRobots) {
                    if (otherRobot->getPosition() == attackedRobotPosition) {
                        someRobotsAttackedInThisIteration = true;
                        otherRobot->actionAttack(*state, attackedRobotPosition);
                        break;//don't look for other robots as it's impossible to have other robots on the same cell (at this point)
                    }
                }
            }
        }

        livingRobots = getLivingRobots();//reload the list after attacks

        //Get and apply moves
        for (RobotState *state: livingRobots) {
            Message message = state->getAction();

            if (message.msg == MessageType::ActionMove) {
                state->actionMove(message.robots.at(0));//apply the move
            }
        }

        //After moves, check collisions (2 robots on the same case) and apply rules of collision
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

        livingRobots = getLivingRobots();//reload the list after collisions

        //Manage robots on bonus cells (apply bonus and remove it)
        for (auto robot: livingRobots) {
            for (auto it = boni.begin(); it != boni.end();) {
                if (robot->getPosition() == it->pos) {
                    if (it->type == BonusType::Energy) {
                        robot->actionEnergy(it->value);
                    } else {
                        robot->actionPower(it->value);
                    }
                    it = boni.erase(it);//after erase, the pointer is incremented so we must take the new value
                } else {
                    it++;//if no there was no remove, we have to manually increment the iterator
                }
            }
        }

        // Manage radar actions
        for (RobotState *state: livingRobots) {
            Message message = state->getAction();
            if (message.msg == MessageType::ActionRadar) {
                state->actionRadar(positions, boniPositions);
                //Send a robot update to all other robots (containing the direction of the robot running the radar)
                for (RobotState *otherRobot: livingRobots) {
                    if (otherRobot != state) {
                        otherRobot->actionRadar({state->getPosition()});
                    }
                }
            }
        }

        //Generate new bonus each 20/nbRobots iteration (iterationCount starts at 1 to avoid having a bonus for the first iteration)
        if (iterationCount % (20 / nbRobots) == 0) {
            BonusType type = (getRandomNumber(0, 2) == 0 ? BonusType::Energy
                                                         : BonusType::Power);//Choose randomly the type of bonus (energy or power)
            Bonus bonus(size, size, (type == BonusType::Energy ? BONUS_MAX_ENERGY : BONUS_MAX_POWER),
                        type);//Create the bonus with a random maximum (depending on the bonus type)
            boni.push_back(bonus);

            //Alert all robots about the new bonus
            for (RobotState *state: livingRobots) {
                state->actionBonus(bonus.pos);
            }
        }

        if (!someRobotsAttackedInThisIteration) {
            iterationWithoutAttack++;
        }

        //Display board and wait only if the display mode is enabled
        if (displayMode) {
            printBoard(iterationCount);
            std::this_thread::sleep_for(SLEEP_TIME_BETWEEN_LOOP);//little sleep before next reload
        }
    }

    //Display the winner or the reason of game stop and return the winner name
    if (displayMode) {
        printBoard(iterationCount);
    }
    vector<RobotState *> finalLivingRobots = getLivingRobots();
    string winner;
    Display::DString d;
    if (finalLivingRobots.size() == 1) {
        winner = finalLivingRobots.at(0)->getName();
        d.setColor(Display::Color::ORANGE);
        d << "The winner is " << winner << "\n\n";
    } else {
        d.setColor(Display::Color::BLUE);
        d << "The game stopped because " << (100 * nbRobots) << " turns have happened without any attack...\n\n";
        if (displayMode) {
            printStats(iterationCount);
        }
    }
    if (displayMode) {
        d.print();
    }
    return winner;
}

void Game::generateRobots(const vector<RobotPack> &robotPacks) {
    for (const RobotPack &pack: robotPacks) {
        int randomX, randomY;
        for (int i = 1; i <= pack.number; i++) {
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
            } else if (pack.className == "BetterR") {
                auto *robot = new BetterR();
                robot->setConfig(size, size, BASE_ENERGY, BASE_POWER);
                robots.push_back(RobotState(robot, pos, size, BASE_ENERGY, BASE_POWER));
            }
        }
    }
}

vector<RobotState *> Game::getLivingRobots() {
    vector<RobotState *> filteredList;

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
    for (const RobotState &state: robots) {
        if (!state.isDead()) {
            Display::DString &cell = board.at(state.getPosition().getX()).at(state.getPosition().getY());
            Display::Color cellColor;
            switch (state.getAction().msg) {
                case MessageType::ActionAttack:
                    cellColor = Display::Color::BLUE;
                    break;
                case MessageType::ActionMove:
                    cellColor = Display::Color::GREEN;
                    break;
                case MessageType::ActionRadar:
                    cellColor = Display::Color::RED;
                    break;
                case MessageType::ActionWait:
                default:
                    cellColor = Display::Color::YELLOW;
            }
            cell.setColor(cellColor);
            cell << to_string(index);
        }
        index++;
    }
    for (const Bonus &bonus: boni) {
        Display::DString &cell = board.at(bonus.pos.getX()).at(bonus.pos.getY());
        cell.setColor(Display::Color::YELLOW);
        cell << CELL_BONUS_CHAR;
    }

    return board;
}

void Game::printBoard(unsigned iterationCount) {
    //Create an empty board
    vector<vector<Display::DString>> board = buildDynamicBoard();

    Display::clearScreen();

    Display::DString d(Display::Color::AQUA);
    d << "LastRobotStanding - Game in progress:\n\n";
    d.setColor(Display::Color::WHITE);
    d << Display::displayGrid<Display::DString>(board, false);
    d.print();

    printStats(iterationCount);
}

void Game::printStats(unsigned iterationCount) {

    ostringstream header;

    header << endl
           << "Tour " << iterationCount << endl
           << "ID "
           << setw(13) << left << "Name"
           << setw(9) << left << "Position"
           << setw(7) << left << "Energy"
           << setw(6) << left << "Power"
           << "Action/Cause of death" << endl;
    Display::DString headerPrinter(Display::Color::ORANGE);
    headerPrinter << header.str();
    headerPrinter.print();

    unsigned index = 1;
    for (const RobotState &state: robots) {
        printStat(state, index);
        index++;
    }
}

void Game::printStat(const RobotState &state, unsigned index) {
    Display::DString stat;
    ostringstream stream;

    stream << setw(2) << index << " " << setw(13) << left << state.getName()
           << "(" << right << setw(2) << state.getPosition().getX() << ","
           << setw(3) << right << state.getPosition().getY() << ") "
           << setw(6) << right << state.getEnergy() << " "
           << setw(5) << right << state.getPower() << " ";

    if (state.isDead()) {
        stat.setColor(Display::Color::RED);
        stream << state.getDeathCause() << endl;
    } else {
        stat.setColor(Display::Color::GREEN);
        Message action = state.getAction();
        ostringstream position;

        if (action.msg == MessageType::ActionAttack || action.msg == MessageType::ActionMove) {
            // position << " (" << setw(3) << action.robots.at(0).getdX()
            //  << "," << setw(3) << action.robots.at(0).getY() << ")";
            position << " " << action.robots.at(0);
        }
        stream << state.getAction().getMessageType()
               << position.str() << endl;
    }
    stat << stream.str();
    stat.print();
}