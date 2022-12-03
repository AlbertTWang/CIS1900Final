#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player
{
    private:
        string name;
        int wood;
        int brick;
        int wheat;
        int sheep;
        int ore;
        int VPs;
        
    public:
        Player(string name, int wood, int brick, int wheat, int sheep, int ore, int VPs);
        
        string getName();
        int getWood();
        int getBrick();
        int getWheat();
        int getSheep();
        int getOre();
        int getVPs();
        
        void setWood(int addedWood);
        void setBrick(int addedBrick);
        void setWheat(int addedWheat);
        void setSheep(int addedSheep);
        void setOre(int addedOre);
        void setVPs(int addedVPs);
};

#endif