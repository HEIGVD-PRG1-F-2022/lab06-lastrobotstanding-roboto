//
// Created by s4rac on 30.11.2022.
//

#ifndef REFACTOR_ROBOTO_H
#define REFACTOR_ROBOTO_H


#include "../const.h"
#include <iostream>
#include <librobots/Robot.h>
#include <vector>

using namespace std;

class Roboto : Robot {
    size_t width, height;
    unsigned energy, power;
    vector<vector<Case>> board;

    void extractBoard(string update);   //fonction
    Damage receiveDamage(string update);//fonction
    string chooseAction();

public:
    Roboto(size_t width, size_t height, unsigned energy, unsigned power);//constructeur
    void setConfig(size_t w, size_t h, unsigned e, unsigned p);
    string action(vector<string> updates);//fonction: recoit les updates(string) de game, return l'action qu'il fait en conséquence
    string name() const;
    Case readOnBoard(int relativeX, int relativeY);
};


#endif//REFACTOR_ROBOTO_H
