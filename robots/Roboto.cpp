#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
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

    for (string update: updates) {
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

string Roboto::chooseAction(UpdatesPack pack) {
    //TODO: Implement roboto strategy

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
                if (direction.mag() <= 2) {//if touching bonus
                    for (Direction directionRobot: robotsDirections) {
                        //TODO: c'est +?
                        if ((direction + directionRobot).mag() <= 2) {
                            return Message::actionAttack(directionRobot);
                        }
                    }
                    //Else take the bonus
                    return Message::actionMove(direction);
                    //TODO: touching robot
                } else if (touchingAnotherRobot) {//if touching robot
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
                    if (direction.mag() >= (direction + directionRobot).mag()) {
                        //TODO: celui-là?
                        return Message::actionAttack(directionRobot);
                    }
                }
                return Message::actionMove(direction);
            }
        } else if (!robotsDirections.empty()) {//else if robots in zone
            //Move to escapeDirection(board)
        } else {
            Direction directionDiag(-1, -1);
            return Message::actionMove(directionDiag);
        }
    }

    minEnergyLevel += (iteration % (20 / nbRobots) == 0) ? 1 : 0;
    iteration++;

    return Message::actionWait();
}

Direction Roboto::escapeDirection(string board, vector<Direction> robotsDirections) {
    Direction direction(0, 0);

    //    Map touchingRobotsPerCells
    //TODO: remplacer par FOR EACH

    map<int, int> touchingRobotsPerCells;

    for (int i = -1; i = 1; i++) {
        for (int j = -1; j = 1; j++) {
            for (auto rDirection: robotsDirections) {
                Position robotPosition = Position(0, 0) + rDirection;
                // Position = Position(0, 0) + ;
            }
        }
    }

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
    return direction;
}
