/*
-----------------------------------------------------------------------------------
Nom du fichier  : helper.cpp
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#include "helper.h"

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}