#include "Roboto.h"
#include <iostream>


Roboto::Roboto(size_t width, size_t height, unsigned energy, unsigned power): width(width), height(height), energy(energy), power(power){

}
void Roboto::setConfig(size_t w, size_t h, unsigned e, unsigned p){
    width = w;
    height = h;
    energy = e;
    power = p;

}
string Roboto::action(vector<string> updates){

}
string Roboto::name(){
    return "NomDeNotreRobot";
}
Case Roboto::readOnBoard(int relativeX, int relativeY){

}

//private

void Roboto::extractBoard(string update){

}
Damage Roboto::receiveDamage(string update){

}
string Roboto::chooseAction(){

}
