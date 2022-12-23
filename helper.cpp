#include "helper.h"

int getRandomNumber(int min, int max) {
    return rand() % (max - min) + min;
}