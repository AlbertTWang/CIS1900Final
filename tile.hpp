#ifndef TILE_HPP
#define TILE_HPP

#define UNCLAIMED_TILE 1
#define CLAIMED_TILE 2
#define UPGRADED_TILE 3
#define PRINTING_LINE_NUMBERS 6

#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

enum TileType{WOOD, BRICK, SHEEP, WHEAT, ORE};

class Tile
{
    protected:
        int tile_owner;
        int tile_number;
        TileType tile_type;
        std::string owner_name;
        bool hasRobber;
    public:
        Tile(int, int, TileType, std::string, bool);
        Tile();
        virtual ~Tile() = 0;
        int get_tile_owner();
        TileType get_tile_type();
        int get_tile_number();
        std::string get_owner_name();
        bool get_hasRobber();
        void set_tile_owner(int);
        void set_tile_number(int);
        void set_tile_type(TileType tile_type);
        void set_owner_name(std::string ownerName);
        void set_hasRobber(bool robber);
        virtual std::string print(int i) const = 0;
        virtual int getTileClass() const = 0;

};

#endif