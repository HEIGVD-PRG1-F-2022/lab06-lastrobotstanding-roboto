/*
-----------------------------------------------------------------------------------
Nom du fichier  : Roboto.cpp
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using namespace std;

void Roboto::setConfig(size_t w, size_t h, unsigned e, unsigned p) {
    width = w;
    height = h;
    energy = e;
    power = p;
    //TODO: should we initialize the board or not ?
    // board = vector<vector<Case>>(w, vector<string>(h, EMPTY));
}

UpdatesPack Roboto::receiveUpdates(const vector<string> &updates) {
    Message boardUpdate = Message(
            updates.at(0));//the boardUpdate is always the first update (see code of RobotState::sendUpdate())

    UpdatesPack pack = {.boardUpdate = boardUpdate};//create the pack with the boardUpdate (the only attribute that don't have a default constructor)

    for (const string &update: updates) {
        Message message(update);

        //Extract UpdateBonus and UpdateDamage message for the pack (and apply damage)
        if (message.msg == MessageType::UpdateBonus) {
            pack.bonusUpdates.push_back(message);
        }
        if (message.msg == MessageType::UpdateDamage) {
            energy -= message.energy;
            pack.damageUpdates.push_back(message);
        }

        //Apply energy and power gains
        if (message.msg == MessageType::UpdateEnergy) {
            energy += message.energy;
        }
        if (message.msg == MessageType::UpdatePower) {
            power += message.power;
        }
    }
    return pack;
}

string Roboto::action(vector<string> updates) {
    return chooseAction(receiveUpdates(updates));
}

string Roboto::name() const {
    return "Roboto";
}

string Roboto::chooseAction(const UpdatesPack &pack) {

    const unsigned nbRobots = pow((width / 10), 2);
    vector<Direction> robotsDirections = pack.boardUpdate.robots;
    vector<Direction> boniDirections = pack.boardUpdate.boni;
    if (energy > minEnergyLevel) {//if a lot of energy

        if (!boniDirections.empty()) {//if bonus in zone

            //Are we touching another robot ?
            bool touchingAnotherRobot = false;
            for (Direction rDirection: robotsDirections) {
                if (rDirection.mag() <= 2) {
                    touchingAnotherRobot = true;
                }
            }

            for (Direction direction: boniDirections) {
                if (direction.mag() <= 2) {//if bonus is touching us
                    for (Direction directionRobot: robotsDirections) {
                        if ((Position(direction.getdX(), direction.getdY()).directionTo(Position(directionRobot.getdX(), direction.getdY()))).mag() <= 2) {
                            return Message::actionAttack(directionRobot);
                        }
                    }
                    //Else take the bonus
                    return Message::actionMove(direction);
                } else if (touchingAnotherRobot) {//if touching robot
                    sort(robotsDirections.begin(), robotsDirections.end(),
                         [](Direction first, Direction second) -> bool {
                             return first.mag() < second.mag();
                         });
                    return Message::actionAttack(robotsDirections.at(0));//attack closest
                } else if (direction.mag() <= 3) {                       //if bonus is a distant one
                    return Message::actionMove(direction);               //move a first step in the direction of the bonus (will touch it at the next round)

                } else {
                    //Attack the closest (could be a distant one...)
                    sort(robotsDirections.begin(), robotsDirections.end(),
                         [](Direction first, Direction second) -> bool {
                             return first.mag() < second.mag();
                         });
                    return Message::actionAttack(robotsDirections.at(0));//attack closest
                }
            }
        } else {                            //no bonus in zone
            if (!robotsDirections.empty()) {//if robots in zone
                // find the closest robot
                sort(robotsDirections.begin(), robotsDirections.end(), [](Direction first, Direction second) -> bool {
                    return first.mag() < second.mag();
                });
                return Message::actionAttack(robotsDirections.at(0));//attack closest
            }
        }
        Direction directionDiag(-1, -1);
        return Message::actionMove(directionDiag);

    } else {                          //if not a lot of energy
        if (!boniDirections.empty()) {//if bonus in zone
            for (Direction direction: boniDirections) {
                for (Direction directionRobot: robotsDirections) {
                    if (direction.mag() >= (Position(direction.getdX(), direction.getdY()).directionTo(Position(directionRobot.getdX(), directionRobot.getdY()))).mag()) {
                        return Message::actionAttack(directionRobot);
                    }
                }
                return Message::actionMove(direction);
            }
        } else if (!robotsDirections.empty()) {//else if robots in zone
                                               //Move to escapeDirection(board)
            return Message::actionMove(escapeDirection(robotsDirections));
        } else {
            Direction directionDiag(-1, -1);
            return Message::actionMove(directionDiag);
        }
    }

    minEnergyLevel += (iteration % (20 / nbRobots) == 0) ? 1 : 0;
    iteration++;

    return Message::actionWait();
}

Direction Roboto::escapeDirection(const vector<Direction> &robotsDirections) {

    //    Map touchingRobotsPerCells

    vector<int> touchingRobotsPerCells;
    vector<int> distantRobotsPerCells;
    vector<Direction> cellDirections;

    int numberOfTouchingRobotsForThisCell = 0;
    int numberOfDistantRobotsForThisCell = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            cellDirections.push_back(Direction(i, j));
            numberOfTouchingRobotsForThisCell = 0;
            for (auto rDirection: robotsDirections) {
                Position robotPosition = Position(0, 0) + rDirection;
                double distance = robotPosition.directionTo(Position(i, j)).mag();
                if (distance < 2) {
                    numberOfTouchingRobotsForThisCell++;
                }
                if (distance <= 3 && distance >= 2) {
                    numberOfDistantRobotsForThisCell++;
                }
            }
            touchingRobotsPerCells.push_back(numberOfTouchingRobotsForThisCell);
            distantRobotsPerCells.push_back(numberOfDistantRobotsForThisCell);
        }
    }

    sort(touchingRobotsPerCells.begin(), touchingRobotsPerCells.end());

    int minIndex = 0;
    int minFound = touchingRobotsPerCells.at(0);
    int index = 0;
    for (auto count: touchingRobotsPerCells) {
        if (count < minFound) {
            minIndex = index;
        }
        index++;
    }
    return cellDirections.at(minIndex);

    //    FOR EACH touching cell including self cell around the robot
    //    Calculate number of touching robots
    //    Store number in a map touchingRobotsPerCells at index cell
    //    Calculate number of distant robots (magnitude >= 2)
    //    Store number in a map distantRobotsPerCells at index cell
    //
    //    Sort the touchingRobotsPerCells map by ascending value
    //
    //    IF there is only 1 touchingRobot for on of the cell
    //    Move to this cell
    //    ELSE IF more than 1 touchingRobot for on of the cell
    // return direction;
}
