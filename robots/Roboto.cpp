#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

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
    // board = vector<vector<Case>>(w, vector<string>(h, EMPTY));
}
int NewgetRandomNumber(int min, int max) {
    std::random_device rd;                           // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());                          // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max);// Guaranteed unbiased
    auto random_integer = uni(rng);
    return random_integer;
}
string Roboto::action(vector<string> updates) {
    //Dumb temporary behavior just for game development phase
    // cout << "action is move 1 -1";
    // return Message::actionMove(Direction(1, 1));
    cout << "X update to manage: " << updates.size();
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
    return Message::actionMove(Direction(NewgetRandomNumber(-1, 1), NewgetRandomNumber(-1, 1)));
}
string Roboto::name() const {
    return "NomDeNotreRobot";
}
// Case Roboto::readOnBoard(int relativeX, int relativeY) {
// }

// //private

// void Roboto::extractBoard(string update) {
// }
// Damage Roboto::receiveDamage(string update) {
// }
// string Roboto::chooseAction() {
// }
