//
// Created by s4rac on 30.11.2022.
//

#ifndef REFACTOR_ROBOTO_H
#define REFACTOR_ROBOTO_H


#include <iostream>
#include <vector>
#include "../const.h"

using namespace std;

class Roboto {
    size_t width, height;
    unsigned energy, power;
    vector<vector<Case>> board;

    void extractBoard(string update); //fonction
    Damage receiveDamage(string update); //fonction
public:
    Roboto(size_t width, size_t height, unsigned energy, unsigned power); //constructeur
    string action(vector<string> updates); //fonction
    string name();
};


#endif //REFACTOR_ROBOTO_H
