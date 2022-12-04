
#ifndef REFACTOR_ROBOTSTATE_H
#define REFACTOR_ROBOTSTATE_H

#include <iostream>
#include "robots/Roboto.h"

class RobotState {
    int x;
    int y;
    unsigned energy;
    unsigned power;
    string lastAction;
    Roboto robot;
public:
    RobotState(int x, int y, unsigned energy, unsigned power, size_t width, size_t height);
    int getX() const;
    int getY() const;
    unsigned getEnergy() const;
    unsigned getPower() const;
    string askAction(vector<string> updates);
    string getLastAction() const;
};

#endif //REFACTOR_ROBOTSTATE_H
