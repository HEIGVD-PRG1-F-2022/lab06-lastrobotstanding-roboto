//
// Created by s4rac on 30.11.2022.
//

#ifndef RANDOM_ROBOT_H
#define RANDOM_ROBOT_H

#include <librobots/Message.h>
#include <librobots/Robot.h>
#include <string>
#include <vector>

class RandomRoboto : public Robot {
    size_t width, height;
    unsigned energy, power;
    // std::vector<std::vector<Case>> board;

    Message receiveDamage(std::string update);//fonction
    std::string chooseAction();

public:
    RandomRoboto() = default;
    virtual void setConfig(size_t w, size_t h, unsigned e, unsigned p);
    std::string action(std::vector<std::string> updates);//fonction: recoit les updates(string) de game, return l'action qu'il fait en conséquence
    std::string name() const;
    // Case readOnBoard(int relativeX, int relativeY);
};


#endif//RANDOM_ROBOT_H
