#include "helper.h"
#include <random>

int getRandomNumber(int min, int max) {
    return rand() % (max - min) + min;
}