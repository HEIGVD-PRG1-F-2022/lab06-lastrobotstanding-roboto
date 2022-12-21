#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <algorithm>
#include <iostream>
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
    Message boardUpdate = Message(updates.at(0));//the boardUpdate is always the first update (see code of RobotState::sendUpdate())

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
            for (Direction direction: boniDirections) {
                if (direction.mag() <= 2) {//if touching bonus
                    // if (/*another robot touching bonus*/) {
                    //     //return Message::actionAttack(OTHER_ROBOT_DIRECTION);
                    // } else {//no robot touching bonus
                    //     //return Message::actionMove(BONUS_DIRECTION);
                    // }
                }
                //ELSE IF robot touching
                //  attack the closest robot
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

    } else {                          //if not a lot of energy
        if (!boniDirections.empty()) {//if bonus in zone
            // if (/*no other robot nearer than us*/) {
            //     //return Message::actionMove(BONUS_DIRECTION);
            // } else {//if robot nearer than us
            //     //return Message::actionAttack(THE_CLOSEST_ROBOT_FROM_BONUS);
            // }
        } else if (!robotsDirections.empty()) {//else if robots in zone
            //Move to escapeDirection(board)
        } else {
            //return Message::actionMove(XXX);
        }
    }

    minEnergyLevel += (iteration % (20 / nbRobots) == 0) ? 1 : 0;
    iteration++;

    return Message::actionWait();
}

Direction Roboto::escapeDirection(string board) {
    Direction direction(0, 0);
    //    Map touchingRobotsPerCells
    //
    //
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
