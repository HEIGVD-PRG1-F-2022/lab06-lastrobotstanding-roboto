//
// Created by s4rac on 30.11.2022.
//

#ifndef REFACTOR_GAME_H
#define REFACTOR_GAME_H

#include <iostream>
#include <vector>
#include "robots/Roboto.h"
#include "RobotState.h"

using namespace std;

class Game {
    vector<RobotState> robots;

public:
    const size_t size;
    Game(unsigned nbRobots); //constructeur
    void generateRobots(); //fonction
};


#endif //REFACTOR_GAME_H
