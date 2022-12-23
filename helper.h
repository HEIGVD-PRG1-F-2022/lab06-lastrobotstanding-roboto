/*
-----------------------------------------------------------------------------------
Nom du fichier  : helper.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef HELPER_H
#define HELPER_H
#include <string>

//Generate a random number in the interval [min; max] (max included)
int getRandomNumber(int min, int max);

//RobotPack used to inform the game how much robots must be created on the board
struct RobotPack {
    std::string className;
    int number;
};
#endif