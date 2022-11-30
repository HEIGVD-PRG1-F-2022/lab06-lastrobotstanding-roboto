#include "RobotState.h"
#include "robots/Roboto.h"

RobotState::RobotState(int x, int y, unsigned energy, unsigned power, size_t width, size_t height): x(x), y(y), energy(energy), power(power), robot(width, height, energy, power){
}