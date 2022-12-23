/*
-----------------------------------------------------------------------------------
Nom du fichier  : BetterR.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef BETTER_R_H
#define BETTER_R_H

#include "Roboto.h"
#include <librobots/Message.h>
#include <string>
#include <vector>


class BetterR : public Roboto {
    std::string chooseAction(const UpdatesPack &pack);//implements the strategy of the action for each round

public:
    BetterR() = default;
    std::string action(std::vector<std::string> updates) override;//ask the robot action
    std::string name() const override;                            //get the name of the robot
};


#endif//BETTER_R_H
