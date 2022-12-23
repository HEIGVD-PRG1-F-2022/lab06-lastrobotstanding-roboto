/*
-----------------------------------------------------------------------------------
Nom du fichier  : Game.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef REFACTOR_GAME_H
#define REFACTOR_GAME_H
#include "helper.h"
#include "libdio/display.h"
#include "librobots/Bonus.h"
#include "librobots/RobotState.h"
#include "robots/Roboto.h"
#include <iostream>
#include <string>
#include <vector>


class Game {
    std::vector<RobotState> robots;
    std::vector<Bonus> boni;
    unsigned nbRobots;

public:
    // recoit les actions des robots, les applique, écrit les string update et les envoie aux robots
    size_t size;                     //pas constant sinon le compilateur ne me laisse pas l'initialiser séparément
    explicit Game(unsigned nbRobots);//constructeur
    std::string start(std::vector<RobotPack> robotPacks, bool displayMode = true);
    void generateRobots(const std::vector<RobotPack>& robotPacks);//fonction
    std::vector<RobotState *> getLivingRobots();
    void printBoard(unsigned iterationCount, bool GameIsFinished);
    std::vector<std::vector<Display::DString>> buildDynamicBoard();
    void printStats(unsigned iterationCount, bool gameIsFinished);
    static void printStat(const RobotState& state, unsigned index);
};


#endif//REFACTOR_GAME_H
