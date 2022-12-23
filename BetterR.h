
#ifndef BETTER_R_H
#define BETTER_R_H

#include "robots/Roboto.h"
#include <librobots/Message.h>
#include <string>
#include <vector>


class BetterR {
    std::string chooseAction(UpdatesPack pack);

public:
    BetterR() = default;
    std::string action(std::vector<std::string> updates);
    std::string name() const;
};


#endif//BETTER_R_H
