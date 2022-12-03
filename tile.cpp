#include <iostream>
#include <iomanip>
#include "tile.h"
#include "player.h"

void Tile::setNumber(int n){
    number = n;
}

void Tile::setLand(LandType l){
    land = l;
}

int Tile::getNumber(){
    return number;
}

LandType Tile::getLand(){
    return land;
}