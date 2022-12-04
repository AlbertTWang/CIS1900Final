#ifndef LAND_H
#define LAND_H

#include <iostream>
#include <sstream>

using namespace std;

enum LandType{WOOD, BRICK, WHEAT, SHEEP, ORE};

class Tile {
    protected:
        int number;
        LandType land;
    
    public:
        void setNumber(int);
        void setLand(LandType);
        int getNumber();
        LandType getLand();
};

#endif