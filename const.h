//
// Created by s4rac on 30.11.2022.
//

#ifndef REFACTOR_CONST_H
#define REFACTOR_CONST_H
enum Case { EMPTY, SELF, OTHER, BONUS };

struct Damage {
    int attackerX;
    int attackerY;
    unsigned energyLoss;
};

#endif //REFACTOR_CONST_H
