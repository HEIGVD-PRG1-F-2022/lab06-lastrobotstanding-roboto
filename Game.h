#ifndef REFACTOR_GAME_H
#define REFACTOR_GAME_H

#include <iostream>
#include <vector>
#include "robots/Roboto.h"
#include "RobotState.h"

using namespace std;

class Game {
    vector<RobotState> robots;
    unsigned nbRobots;
public:
    // recoit les actions des robots, les applique, écrit les string update et les envoie aux robots
    size_t size; //pas constant sinon le compilateur ne me laisse pas l'initialiser séparément
    Game(unsigned nbRobots); //constructeur
    void generateRobots(unsigned nbRobots); //fonction
};


#endif //REFACTOR_GAME_H
