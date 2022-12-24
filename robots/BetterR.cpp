/*
-----------------------------------------------------------------------------------
Nom du fichier  : BetterR.cpp
Auteur(s)       : Samuel Roland, Sara Camassa
Date creation   : 29.11.2022
Description     : Last Robot Standing
-----------------------------------------------------------------------------------
*/
#include "BetterR.h"
#include "Roboto.h"
#include "librobots/Direction.h"
#include "librobots/Message.h"
#include <vector>

using namespace std;

//Apply updates and choose the action for this round
string BetterR::action(vector<string> updates) {
    return chooseAction(receiveUpdates(updates));
}

string BetterR::name() const {
    return "BetterR";
}

//The strategy here is just a diagonal move
string BetterR::chooseAction(const UpdatesPack &pack) {
    return Message::actionMove(Direction(-1, 0));
}
