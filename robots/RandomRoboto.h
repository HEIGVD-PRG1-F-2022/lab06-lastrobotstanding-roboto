/*
-----------------------------------------------------------------------------------
Nom du fichier  : RandomRoboto.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef RANDOM_ROBOTO_H
#define RANDOM_ROBOTO_H

#include "Roboto.h"
#include <librobots/Message.h>
#include <string>
#include <vector>

class RandomRoboto : public Roboto {
    std::string chooseAction(const UpdatesPack &pack);//implements the strategy of the action for each round

public:
    RandomRoboto() = default;
    std::string action(std::vector<std::string> updates) override;//ask the robot action
    [[nodiscard]] std::string name() const override;              //get the name of the robot
};


#endif//RANDOM_ROBOTO_H
