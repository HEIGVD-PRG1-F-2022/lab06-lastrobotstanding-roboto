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

string Roboto::action(vector<string> updates) {
    //TODO: extract updates (board, damage, bonus) apply them and call chooseAction()

    //Dumb temporary behavior just for game development phase
    // cout << "action is move 1 -1";
    // return Message::actionMove(Direction(1, 1));
    for (string update: updates) {
        Message message(update);
        if (message.msg == MessageType::UpdateBonus) {
            vector<Direction> bonusDirections = message.boni;
            if (!bonusDirections.empty()) {

                //Sort by growing magnitude to have the nearest robot
                sort(bonusDirections.begin(), bonusDirections.end(), [](Direction first, Direction second) -> bool {
                    return first.mag() < second.mag();
                });
                return Message::actionMove(bonusDirections.at(0));
            }
        }
        if (message.msg == MessageType::UpdateBoard) {
            for (Direction direction: message.robots) {
                if (direction.mag() <= 2) {
                    return Message::actionAttack(direction);
                }
            }
            chooseAction(message);
        }
        if (message.msg == MessageType::UpdateDamage) {
            energy -= message.energy;
        }
        if (message.msg == MessageType::UpdateEnergy) {
            energy += message.energy;
        }
        if (message.msg == MessageType::UpdatePower) {
            power += message.power;
        }
    }
    return Message::actionMove(Direction(rand() % (1 + 1) - 1, rand() % (1 + 1) - 1));
}

string Roboto::name() const {
    return "Roboto";
}
// Case Roboto::readOnBoard(int relativeX, int relativeY) {
// }

// //private

// Damage Roboto::receiveDamage(string update) {
// }
string Roboto::chooseAction(Message message) {
    //TODO: Implement roboto strategy

    const unsigned nbRobots = pow((width / 10), 2);
    vector<Direction> robotsDirections = message.robots;
    vector<Direction> boniDirections = message.boni;
    if (energy > minEnergyLevel) { //if a lot of energy

        if (!boniDirections.empty()) { //if bonus in zone
            for (Direction direction: boniDirections) {
                if (direction.mag() <= 1) { //if touching bonus
                    if (/*another robot touching bonus*/) {
                        //return Message::actionAttack(OTHER_ROBOT_DIRECTION);
                    } else { //no robot touching bonus
                        //return Message::actionMove(BONUS_DIRECTION);
                    }
                }
                //ELSE IF robot touching
                //  attack the closest robot
            }
        } else { //no bonus in zone
            if (!robotsDirections.empty()) { //if robots in zone
                // find the closest robot
                sort(robotsDirections.begin(), robotsDirections.end(), [](Direction first, Direction second) -> bool {
                    return first.mag() < second.mag();
                });
                return Message::actionAttack(robotsDirections.at(0)); //attack closest
            }
        }

    } else { //if not a lot of energy
        if (!boniDirections.empty()){ //if bonus in zone
            if(/*no other robot nearer than us*/){
                //return Message::actionMove(BONUS_DIRECTION);
            }else{ //if robot nearer than us
                //return Message::actionAttack(THE_CLOSEST_ROBOT_FROM_BONUS);
            }
        }
        else if(!robotsDirections.empty()){ //else if robots in zone
            //Move to escapeDirection(board)
        }
        else{
            //return Message::actionMove(XXX);
        }
    }

    minEnergyLevel += (iteration % (20 / nbRobots) == 0) ? 1 : 0;
    iteration++;

    return Message::actionWait();
}

Direction Roboto::escapeDirection(string board){
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
