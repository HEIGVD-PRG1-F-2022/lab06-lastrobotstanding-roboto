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

int getRandomNumber(int min, int max);

//TODO: were should we place this declaration ?
struct RobotPack {
    std::string className;
    int number;
};
#endif