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
        }
        if (message.msg == MessageType::UpdateDamage) {
            energy -= message.energy;
        }
        if(message.msg == MessageType::UpdateEnergy){
            energy += message.energy;
        }
        if(message.msg == MessageType::UpdatePower){
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
string Roboto::chooseAction() {
    //TODO: Implement roboto strategy

    //Si + d'un robot autour -> fuir

    //Si un robot autour (diagonale) ->
    //  Si peu energy -> fuir autre direction
    //  Si bon energy peu power -> ?
    //  Si bon energy bon power -> s'aligner pour attaquer

    //Si un robot en face (ligne/colonne) ->
    //  Si peu energy -> fuir
    //  Si bon energy peu power -> ?
    //  Si bon energy et bon power -> attaquer

    //Si bonus autour ->
    //  Si peu energy -> aller vers bonus
    //  Si bon energy -> ?

    //Radar?
    //Damage?
    //Wait?

    return "";
}
