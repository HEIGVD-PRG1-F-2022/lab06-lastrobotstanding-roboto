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
    std::string chooseAction(UpdatesPack pack);

public:
    RandomRoboto() = default;
    std::string action(std::vector<std::string> updates) override;
    [[nodiscard]] std::string name() const override;
};


#endif//RANDOM_ROBOTO_H
