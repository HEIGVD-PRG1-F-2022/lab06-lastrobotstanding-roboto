//
// Created by s4rac on 30.11.2022.
//

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
    std::string action(std::vector<std::string> updates);
    [[nodiscard]] std::string name() const;
};


#endif//RANDOM_ROBOTO_H
