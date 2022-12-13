#ifndef HELPER_H
#define HELPER_H
#include <string>

int getRandomNumber(int min, int max);

//TODO: were should we place this declaration ?
struct RobotPack {
    std::string className;
    int number;
};
#endif