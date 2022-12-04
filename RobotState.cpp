#include "RobotState.h"
#include "robots/Roboto.h"

RobotState::RobotState(int x, int y, unsigned energy, unsigned power, size_t width, size_t height): x(x), y(y), energy(energy), power(power), robot(width, height, energy, power){

}
int RobotState::getX() const{
    return x;
}
int RobotState::getY() const{
    return y;
}
unsigned RobotState::getEnergy() const{
    return energy;
}
unsigned RobotState::getPower() const {
    return power;
}
string RobotState::askAction(vector<string> updates){
    return "";
}
string RobotState::getLastAction() const{
    return lastAction;
}