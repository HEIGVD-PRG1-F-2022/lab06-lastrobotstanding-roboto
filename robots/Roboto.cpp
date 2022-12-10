#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

//Need constructor for Game.cpp/generateRobots
Roboto::Roboto(size_t width, size_t height, unsigned energy, unsigned power) : width(width), height(height), energy(energy), power(power) {
    this->width = width;
    this->height = height;
    this->energy = energy;
    this->power = power;
}

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
    return "";
}
