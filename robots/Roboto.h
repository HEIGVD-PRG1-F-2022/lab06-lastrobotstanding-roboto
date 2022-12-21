//
// Created by s4rac on 30.11.2022.
//

#ifndef REFACTOR_ROBOTO_H
#define REFACTOR_ROBOTO_H

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

    std::string chooseAction(UpdatesPack pack);
    UpdatesPack receiveUpdates(const std::vector<std::string> &updates);
    Direction escapeDirection(std::string board);

public:
    Roboto() = default;
    virtual void setConfig(size_t w, size_t h, unsigned e, unsigned p);
    std::string action(std::vector<std::string> updates);//fonction: recoit les updates(string) de game, return l'action qu'il fait en conséquence
    std::string name() const;
};


#endif//REFACTOR_ROBOTO_H
