#ifndef REFACTOR_GAME_H
#define REFACTOR_GAME_H


#include "robots/Roboto.h"
#include "librobots/RobotState.h"
#include <iostream>
#include <vector>


using namespace std;

class Game {
    vector<RobotState> robots;
    unsigned nbRobots;

public:
    // recoit les actions des robots, les applique, écrit les string update et les envoie aux robots
    size_t size;                     //pas constant sinon le compilateur ne me laisse pas l'initialiser séparément
    explicit Game(unsigned nbRobots);//constructeur
    void start();
    void generateRobots();//fonction
    void printBoard();
    vector<vector<string>> buildDynamicBoard();
    string computeBoardAsString();
};


#endif//REFACTOR_GAME_H
