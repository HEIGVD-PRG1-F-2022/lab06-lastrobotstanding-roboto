/*
-----------------------------------------------------------------------------------
Nom du fichier  : Roboto.h
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#ifndef ROBOTO_H
#define ROBOTO_H

#include <librobots/Direction.h>
#include <librobots/Message.h>
#include <librobots/Robot.h>
#include <string>
#include <vector>

//A pack containing the extracted updates (as Message) useful to the strategy, separated by types
struct UpdatesPack {
    Message boardUpdate;
    std::vector<Message> bonusUpdates;
    std::vector<Message> damageUpdates;
};

class Roboto : public Robot {
    size_t width, height;
    unsigned energy, power;
    unsigned iteration = 0;
    unsigned minEnergyLevel = 10;

    std::string chooseAction(const UpdatesPack &pack);                               	
    static Direction escapeDirection(const std::vector<Direction> &robotsDirections);//choose the better direction when robots around

public:
    Roboto() = default;
    void setConfig(size_t w, size_t h, unsigned e, unsigned p) override;//set the configuration
    UpdatesPack receiveUpdates(const std::vector<std::string> &updates);//receive and apply updates
    std::string action(std::vector<std::string> updates) override;      //ask the robot action
    [[nodiscard]] std::string name() const override;                    //get the name of the robot
};


#endif//ROBOTO_H
