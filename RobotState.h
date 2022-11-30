
#ifndef REFACTOR_ROBOTSTATE_H
#define REFACTOR_ROBOTSTATE_H

#include <iostream>
#include "robots/Roboto.h"

class RobotState {
    int x;
    int y;
    unsigned energy;
    unsigned power;
    Roboto robot;
public:
    RobotState(int x, int y, unsigned energy, unsigned power, size_t width, size_t height);
    int getX();
    int getY();
    unsigned getEnergy();
    unsigned getPower();
};

#endif //REFACTOR_ROBOTSTATE_H
