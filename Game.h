/*
-----------------------------------------------------------------------------------
Nom du fichier  : Game.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef GAME_H
#define GAME_H
#include "helper.h"
#include "libdio/display.h"
#include "librobots/Bonus.h"
#include "librobots/RobotState.h"
#include "robots/Roboto.h"
#include <iostream>
#include <string>
#include <vector>


class Game {
    std::vector<RobotState> robots;//vector of robots in game
    std::vector<Bonus> boni;       //vector of boni in game
    unsigned nbRobots;             //number of robots in game

public:
    size_t size;                                                                  //not constant in order to initialize separately
    explicit Game(unsigned nbRobots);                                             //constructor
    std::string start(std::vector<RobotPack> robotPacks, bool displayMode = true);//main function: receives robots actions, applies them, writes updates strings and sends them to robots
    void generateRobots(const std::vector<RobotPack> &robotPacks);                //generate robots on the board at random coordinates
    std::vector<RobotState *> getLivingRobots();                                  //get vector of all still living robots on board
    void printBoard(unsigned iterationCount);                                     //print the board
    std::vector<std::vector<Display::DString>> buildDynamicBoard();               //build the board updated for each turn with the list of RobotState
    void printStats(unsigned iterationCount);                                     //print the stats for all robots and the turn iteration
    static void printStat(const RobotState &state, unsigned index);               //print the stats for one robot
};


#endif//GAME_H
