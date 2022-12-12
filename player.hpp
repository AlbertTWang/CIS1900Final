#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
using namespace std;

class Player
{
    private:
        string name;
        int wood;
        int brick;
        int sheep;
        int wheat;
        int ore;
        int VPs;
        
    public:
        Player(string name, int wood, int brick, int sheep, int wheat, int ore, int VPs);
        
        string getName();
        int getWood();
        int getBrick();
        int getSheep();
        int getWheat();
        int getOre();
        int getVPs();
        
        void setWood(int addedWood);
        void setBrick(int addedBrick);
        void setSheep(int addedSheep);
        void setWheat(int addedWheat);
        void setOre(int addedOre);
        void setVPs(int addedVPs);
};

#endif