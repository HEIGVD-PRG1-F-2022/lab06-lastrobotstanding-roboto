#ifndef REFACTOR_GAME_H
#define REFACTOR_GAME_H


#include "librobots/RobotState.h"
#include "robots/Roboto.h"
#include <iostream>
#include <vector>


class Game {
    std::vector<RobotState> robots;
    unsigned nbRobots;

public:
    // recoit les actions des robots, les applique, écrit les string update et les envoie aux robots
    size_t size;                     //pas constant sinon le compilateur ne me laisse pas l'initialiser séparément
    explicit Game(unsigned nbRobots);//constructeur
    void start(std::vector<RobotPack> robotPacks);
    void generateRobots(std::vector<RobotPack> robotPacks);//fonction
    std::vector<RobotState *> getLivingRobots();
    void printBoard(unsigned iterationCount);
    std::vector<std::vector<std::string>> buildDynamicBoard();
    void printStats(RobotState state, unsigned index);
};


#endif//REFACTOR_GAME_H
